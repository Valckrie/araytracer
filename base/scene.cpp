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

Colour Scene::raytrace(Ray ray, int level) {
    double ta, t;
    Colour col;

    Object *obj;
    Object *closest;

    Light *lt;
    Hit   hit;

    Vertex position;
    Vector normal;

    int max_depth = 1;
    int cur_depth = level;

    int testvar;
    testvar = 0;
    // cout << "\n cur lvl : " << level << " max lvl " << max_depth;

    if (level > max_depth) {
        col.clear();
        return col; // stop if recursed deep enough
    }

    // TEST EACH OBJECT AGAINST RAY, FIND THE CLOSEST
    // iterate through objects

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

    // colour = black (background colour, havent set option)
    col.clear();
    // col.set(0.5, 0.5, 1.0, 1.0);

    // if ray hit an object
    if (closest != (Object *)0) {
        lt = light_list;

        Colour ocol;

        // commence shading
        Colour ka = closest->obj_mat->ka;
        Colour kd = closest->obj_mat->kd;
        Colour ks = closest->obj_mat->ks;
        Colour kr = closest->obj_mat->kr;
        Colour kt = closest->obj_mat->kt;
        Ray sray;

        // regardless of light, ambient colours
        col.red     += ka.red;
        col.green   += ka.green;
        col.blue    += ka.blue;

        while (lt != (Light *)0) {
            Vector ldir;
            Vector xldir;
            Colour lcol;

            // set light properties
            lt->getLightProperties(position, &xldir, &lcol);
            xldir.normalise();

            // add shadow test here

            // by default, not in a shadow
            bool in_shadow = false;
            Object *obj2;
            Vertex location = lt->getLocation();
            // Vertex location (10, 10, 0, 1);
            double shadowt;
            double d = location.distance(ray.P);       

// check for shadow intersections

            Ray shadowray(position, xldir);
            double shadowhit;

            // cout << shadowhit << "\n";

            if(lt->cast_shadows()) {
                obj2 = obj_list;
                while (obj2 != (Object *)0) {
                    if(obj2->shadow_hit(shadowray, shadowhit)) {
                        // cout << "\n chklpoint 1";
                        if(shadowhit < d) {
                            in_shadow = true;
                        }
                        break;
                    }
                    obj2 = obj2->next();
                }
                // in_shadow stays false
            }

            if(in_shadow == false) {

                // == calculate diffuse component

                double dlc = xldir.dot(normal);
                if (dlc < 0.0) {
                    dlc = 0.0;
                }

                // == calculate specular component

                // normal_dot_light_dir = dlc           // diffuse component
                // light_dir = xldir                    // light direction
                // ray_dir_reversed = xldir reversed    // ray direction reversed 

                Vector light_dir = xldir;
                Vector ray_dir_reversed = ray.D.negative();
                // double normal_dot_light_dir = sr.normal * light_dir;
                double normal_dot_light_dir = light_dir.dot(normal);

                // mirror reflection direction
                // Vector r(-light_dir + 2.0 * sr.normal * normal_dot_light_dir);

                Vector r = light_dir.negative().add(normal.multiply(normal_dot_light_dir).multiply(2.0));
                
                // double specular = r * ray_dir_reversed;        
                double specular = r.dot(ray_dir_reversed);
                specular = pow(specular, 37);

                double slc = specular;
                if (slc < 0.0) {
                    slc = 0.0;
                }

                // combine components
                col.red     += lcol.red *    (dlc * kd.red   + slc * ks.red);
                col.green   += lcol.green *  (dlc * kd.green + slc * ks.green);
                col.blue    += lcol.blue *   (dlc * kd.blue  + slc * ks.blue);

                // L += (  diffuse_brdf->f(sr, wo, wi) + 
                //     specular_brdf->f(sr, wo, wi) ) * sr.w.lights[j]->L(sr) * ndotwi;

                // l + (dlc * kd + slc * ks ) * lcol 
                // the ndotwi is part of specularbrdf already but isnt part of diffuse brdf
                // so thats why its there
            }
            lt = lt->next(); // next light
        }

        // cout << "COLOR : " << col.red << " " << col.green << " " << col.blue;

        // add reflected rays here
        if(kr.red > 0.0 || kr.green > 0.0 || kr.blue > 0.0) {

            // Vector ray_dir = ray.D;
            // Vector n = normal;
            // double ndotrdr = n.dot(ray_dir);
            // Vector r = ray_dir.negative().add(n.multiply(ndotrdr).multiply(-2.0));


            // pi + R * EPSILON
            // if(level < max_depth) {

            // }


            // vector3 N = prim->GetNormal( pi );
            // vector3 R = a_Ray.GetDirection() - 2.0f * DOT( a_Ray.GetDirection(), N ) * N;
            // if (a_Depth < TRACEDEPTH) 
            // {
            //     Color rcol( 0, 0, 0 );
            //     float dist;
            //     Raytrace( Ray( pi + R * EPSILON, R ), rcol, a_Depth + 1, a_RIndex, dist );
            //     a_Acc += refl * rcol * prim->GetMaterial()->GetColor();
            // }


            Vector ray_dir_reversed = ray.D.negative();
            // Vector3D wo = -sr.ray.d;
            Vector light_dir;
            // Vector3D wi;

            double ndotrdr = normal.dot(ray_dir_reversed);
            // double ndotwo = sr.normal * wo;

            light_dir = ray_dir_reversed.negative().add(normal.multiply(ndotrdr).multiply(2.0));
            // wi = -wo + 2.0 * sr.normal * ndotwo; 

            double rlc = fabs(normal.dot(light_dir));
            Colour rlc_col = kr; rlc_col.multiply(rlc);
            // Colour rlc_col = kr.divide(rlc);
            // Colour rlc_col = kr;
            // Colour rlc_col (rlc, rlc, rlc, 1.0);
            // return (kr * cr / fabs(sr.normal * wi));

            // const double ERR = 0.00000000001;
            // Vector normalcopy;
            // normalcopy.set(normal.x, normal.y, normal.z);
            // Vector newr = normalcopy.multiply(ERR);
            // Vertex poscopy = position;
            // Vertex newp = poscopy.addVector(newr);

            // cout << "\n pos " << position.x << " "<< position.y <<" " << position.z;
            // Ray reflected_ray(position.addVector(light_dir.multiply(0.000000000001)), light_dir);

            // .multiply causes perma effect?

            testvar += 1;
            // cout << "\n testvar : " <<testvar ;

            // Vector normal3;
            // Vector normal4;
            // Vector normal5;
            // Vector normal6;
            // Vector normal7;
            // Vector normal2 = normal.multiply(0.001);
            Vertex adjust = position.addVector(normal.multiply(0.001));
            // Ray reflected_ray(position, light_dir);
            Ray reflected_ray(adjust, light_dir);
            // Ray reflected_ray(sr.hit_point, wi);

            // reflected_ray.depth = cur_depth + 1;
            // reflected_ray.depth = sr.depth + 1;
        
            double normal_dot_light_dir = light_dir.dot(normal);
            // col.add(rlc_col);

            // Colour recursive = raytrace(reflected_ray, cur_depth + 1);
            // rlc_col.multiply(recursive);
            // col.add(rlc_col);

            // if(level != 0) cout << "\n cur lvl : " << cur_depth << " max lvl " << max_depth;

            rlc_col.multiply(raytrace(reflected_ray, cur_depth + 1));
            rlc_col.multiply(normal_dot_light_dir);

            // if(level != 0) cout << "\n DEPTH " << level << " COLOR : " << rlc_col.red << " " << rlc_col.green << " " << rlc_col.blue;

            col.add(rlc_col);

            // col.add(Colour(0.1,0.1,0.1,1.0));
            // col.multiply(raytrace(reflected_ray, cur_depth + 1));
            // col.red     += (kr.red / rlc);
            // col.green   += (kr.green / rlc);
            // col.blue    += (kr.blue / rlc);
        }

        

        // add refracted rays here
    } else {
        // no object hit. return background color
        col.set(0.5, 0.5, 1.0, 1.0);
    }

    // otherwise just return col, which is black, (bg col)
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

    double t;
    double d = location.distance(ray.P);

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
    double t;
    int numObjects = sr.w.objects.size();
    double d = location.distance(ray.o);
                                                        
    for (int j = 0; j < num_objects; j++)
        if (sr.w.objects[j]->shadow_hit(ray, t) && t < d)
            return (true); 
                                                        
    return (false);   
    */

    return false;
}