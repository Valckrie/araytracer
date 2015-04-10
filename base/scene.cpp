#include <math.h>
#include <iostream>

#include "include/scene.h"
#include "include/constants.h"
using namespace std;
Scene::Scene()
{
  scache = 0;
  obj_list = (Object *)0;
}

void Scene::addObject(Object &obj)
{
  // reference obj_list as the obj's next pointer - linking
  // then replace obj_list with obj
  // effectively obj is now the object at start of list
  obj.link(obj_list);
  obj_list = &obj;
}

void Scene::addLight(Light &lt)
{
  lt.link(light_list);
  light_list = &lt;
}

Colour Scene::raytrace(Ray &ray, int level) {
    float ta, t;
    Colour col;

    Object *obj;
    Object *closest;

    Light *lt;
    Hit   hit;

    Vertex position;
    Vector normal;

    if (level == 0) {
        col.clear();
        return col; // stop if recursed deep enough
    }

    // TEST EACH OBJECT AGAINST RAY, FIND THE CLOSEST

    t = kHugeValue; // a long way aways
    closest = (Object *)0;
    obj = obj_list;

    while (obj != (Object *)0) {
        if(obj->intersect(ray, &hit) == true) {
            if (hit.t < t) {
                closest = hit.obj;
                // t = min parameter t, 
                t = hit.t;
                normal = hit.n;
                position = hit.p;
            }
        }
        obj = obj->next();
    }

    col.clear();

    if (closest != (Object *)0) {
        lt = light_list;

        Colour ocol;

        Colour ka = closest->obj_mat->ka;
        Colour kd = closest->obj_mat->kd;
        Colour ks = closest->obj_mat->ks;
        Colour kr = closest->obj_mat->kr;
        Colour kt = closest->obj_mat->kt;
        Ray sray;


        while (lt != (Light *)0) {
            Vector ldir;
            Vector xldir;
            Colour lcol;

            // add shadow test here

// == calculate diffuse component

            lt->getLightProperties(position, &xldir, &lcol);
            xldir.normalise();
            float dlc = xldir.dot(normal);
            if (dlc < 0.0) {
                dlc = 0.0;
            }

// == calculate specular component here
            float slc = 0.0;

            // ndotwi = dlc        // diffuse component
            // wi = xldir          // light direction
            // wo = xldir reversed // ray direction reversed 

            Vector wi = xldir;
            Vector wo = ray.D.negative();
            // float ndotwi = sr.normal * wi;
            float ndotwi = wi.dot(normal);

            // mirror reflection direction
            // Vector3D r(-wi + 2.0 * sr.normal * ndotwi);

            // Vector r = wi.negative() + 2.0 * normal * ndotwi;
                // --- vector = vector + vector <-2.0 multiply [vector]// vector mult float [returns vector];
            Vector r = wi.negative().add(normal.multiply(ndotwi).multiply(2.0));
            

            // float rdotwo = r * wo;        
            float rdotwo = r.dot(wo);
            rdotwo = pow(rdotwo, 37);

            // if (rdotwo > 0.0) {
            //     L = ks * cs * pow(rdotwo, exp);
            //     L = ks * cs * pow(rdotwo, 20);
            // }

            // cout << "R" << rdotwo << "\n" ;

            if(rdotwo > 0.0) {
                slc = rdotwo;
            }

            // float slc = rdotwo;
            // if (slc < 0.0) {
            //     slc = 0.0;
            // }

// shadow part



            // cout << "reach pre shadow";

            // check for shadow intersections
            Object *obj2;
            // LOCATION IS LIGHT LOCATION< PASS IN AS PARAMETER
            Vertex location = lt->getLocation();
            // Vertex location (10, 10, 0, 1);

            float shadowt;
            float d = location.distance(ray.P);
            

            bool in_shadow = false;


            Ray shadowray(position, xldir);

            Hit shadowhit;

            if(lt->cast_shadows()) {
                obj2 = obj_list;
                while (obj2 != (Object *)0) {
                    if(obj2->shadow_hit(shadowray, &shadowhit)) {
                        // cout << "\n chklpoint 1";

                        if(shadowhit.t < d) {
                            in_shadow = true;
                        }
                        break;
                    }
                    obj2 = obj2->next();
                }
                // false
            }

// orig shadow func
            // bool in_shadow = false;
            // if(lt->cast_shadows()) {
            //     Ray shadowray(position, xldir);
            //     in_shadow = shadowtrace(shadowray, 10);
            // }

// combine components
            // cout << in_shadow ;
            col.red     += ka.red;
            col.green   += ka.green;
            col.blue    += ka.blue;
            if(in_shadow == false) {
                col.red     += lcol.red *    (dlc * kd.red   + slc * ks.red);
                col.green   += lcol.green *  (dlc * kd.green + slc * ks.green);
                col.blue    += lcol.blue *   (dlc * kd.blue  + slc * ks.blue);
            }

            lt = lt->next(); // next light
        }

    // add reflected rays here

    // add refracted rays here
    }
    return col;
}


bool shadowtrace(Ray &ray, double tlimit)
{

    /*
    cout << "shadow trace";
    // tlimit is d !

    // check for shadow intersections
    Object *obj;
    Object *closest;
    Hit   hit;

    // LOCATION IS LIGHT LOCATION< PASS IN AS PARAMETER
    Vertex location (10, 10, 0, 1);

    float t;
    float d = location.distance(ray.P);

    closest = (Object *)0;
    obj = obj_list;

    while (obj != (Object *)0) {
        if(obj->shadow_hit(ray, t) && t < d) {
            return true;
        }
        obj = obj->next();
    }
    */

    /*
    float t;
    int numObjects = sr.w.objects.size();
    float d = location.distance(ray.o);
                                                        
    for (int j = 0; j < num_objects; j++)
        if (sr.w.objects[j]->shadow_hit(ray, t) && t < d)
            return (true); 
                                                        
    return (false);   
    */

    return false;
}