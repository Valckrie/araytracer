#include <math.h>
#include <iostream>

#include "include/scene.h"
#include "include/constants.h"
using namespace std;

const int MAX_DEPTH = 4;

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

    int cur_depth = level;

    int highest_depth = 0;

    int testvar;
    testvar = 0;
    // cout << "\n cur lvl : " << level << " max lvl " << max_depth;

    if (level > MAX_DEPTH) {
        col.clear();
        return col; // stop if recursed deep enough
    }

    // if(level > 1) {
    //     highest_depth = level;
    //     cout << "\nhighest depth reached : " << highest_depth ;
    // }

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
        double ior = closest->obj_mat->ior;
        int exponent = closest->obj_mat->exponent;
        int material_type = closest->obj_mat->type;
        Ray sray;


        if (material_type == 99) {
            // checkered/tile floor pattern
            int square = (int)floor(position.x) + (int)floor(position.z);
            if ((square % 2) == 0) {
                // black tile
                ka.red = 0.0;
                ka.green = 0.0;
                ka.blue = 0.0;
                kd.red = 0.2;
                kd.green = 0.2;
                kd.blue = 0.2;
            }
            else {
                // white tile
                // ka.red = 1.0;
                // ka.green = 1.0;
                // ka.blue = 1.0;
                // kd.red = 1.0;
                // kd.green = 1.0;
                // kd.blue = 1.0;
            }
        }


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
                specular = pow(specular, exponent);

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
        // if ((kr.red > 0.0 || kr.green > 0.0 || kr.blue > 0.0) &&
        //     (kt.red == 0.0 && kt.green == 0.0 && kt.blue == 0.0)) {

        if(material_type == 3) {

            Vector ray_dir_reversed = ray.D.negative();
            // Vector3D wo = -sr.ray.d;
            Vector light_dir;
            // Vector3D wi;

            double ndotrdr = normal.dot(ray_dir_reversed);
            // double ndotwo = sr.normal * wo;

            light_dir = ray_dir_reversed.negative().add(normal.multiply(ndotrdr).multiply(2.0));
            // wi = -wo + 2.0 * sr.normal * ndotwo; 

            double rlc = fabs(normal.dot(light_dir));
            // Colour rlc_col = kr;
            // rlc_col.multiply(rlc);
            Colour rlc_col = kr.returnDivide(rlc);

            // return (kr * cr / fabs(sr.normal * wi));

            Vertex adjust = position.addVector(normal.multiply(0.001));
            // Ray reflected_ray(position, light_dir);
            Ray reflected_ray(adjust, light_dir);
            // Ray reflected_ray(sr.hit_point, wi);

            double normal_dot_light_dir = light_dir.dot(normal);
            // if(level != 0) cout << "\n cur lvl : " << cur_depth << " max lvl " << max_depth;

            rlc_col.multiply(raytrace(reflected_ray, cur_depth + 1));
            rlc_col.multiply(normal_dot_light_dir);

            // if(level != 0) cout << "\n DEPTH " << level << " COLOR : " << rlc_col.red << " " << rlc_col.green << " " << rlc_col.blue;
            col.add(rlc_col);
        }

// end reflect

// add refracted rays here

        // if(kt.red > 0.0 || kt.green > 0.0 || kt.blue > 0.0) {
        if(material_type == 4) {
            // if no work try avoid same var names

            Vector ray_dir_reversed = ray.D.negative();
            // Vector3D wo = -sr.ray.d;
            Vector light_dir;
            // Vector3D wi;
            double ndotrdr = normal.dot(ray_dir_reversed);
            light_dir = ray_dir_reversed.negative().add(normal.multiply(ndotrdr).multiply(2.0));
            // wi = -wo + 2.0 * sr.normal * ndotwo; 
            double rlc = fabs(normal.dot(light_dir));
            Colour rlc_col = kr; rlc_col.multiply(rlc);
            
            Vertex adjust = position.addVector(normal.multiply(0.001));
            Ray reflected_ray(adjust, light_dir);
            double normal_dot_light_dir = light_dir.dot(normal);
            // rlc_col.multiply(raytrace(reflected_ray, cur_depth + 1));
            // rlc_col.multiply(normal_dot_light_dir);
            // col.add(rlc_col);

        // new part for refraction

            bool total_internal_reflection = false;


        // tir
            // wo
            double cos_thetai = normal.dot(ray_dir_reversed);
            // index of refraction
            double eta = ior;
            if(cos_thetai < 0.0) {
                eta = 1.0 / eta;
            }
            double temp = 1.0 - (1.0 - cos_thetai * cos_thetai) / (eta * eta);
            total_internal_reflection = temp < 0.0;
            // if(temp < 0.0) total_internal_reflection = true;
        // end tir

            if(total_internal_reflection == true) {

                // cout << "TIR TRUE\n";
                // continued from above
                rlc_col.multiply(raytrace(reflected_ray, cur_depth + 1));
                // rlc_col.multiply(normal_dot_light_dir);
                col.add(rlc_col);
            } else {

                // cout << "TIR FALSE\n";

                Vector wt;
        // below is the sample_f return

                Vector n = normal;
                // wo
                // reset this value
                cos_thetai = n.dot(ray_dir_reversed);
                // reset this value
                eta = ior;

                if(cos_thetai < 0.0) {
                    cos_thetai = -cos_thetai;
                    n = n.negative();
                    eta = 1.0 / eta;
                }
                // recalculate
                temp = 1.0 - (1.0 - cos_thetai * cos_thetai) / (eta * eta);
                double cos_theta2 = sqrt(temp);

                // dvide changes the shadow for some random reason.
                Vector tmp1 = ray_dir_reversed.negative().divide(eta);
                Vector tmp2 = n.multiply((cos_theta2 - cos_thetai / eta));
                wt = tmp1.subtract(tmp2);

                Colour refracted (1.0, 1.0, 1.0, 1.0);
                // Colour refracted;
                double ktv = 0.9;
                double ttt = ktv / (eta * eta);
                refracted.changeDivide(fabs(normal.dot(wt)));
                refracted.multiply(ttt);
        // end samplef, return colour refracted

                // Vertex adjust2 = position.addVector(normal.multiply(0.001));
                // Ray transmitted_ray(adjust2, light_dir);
                Ray transmitted_ray(position, wt);

                rlc_col.multiply(raytrace(reflected_ray, cur_depth + 1));
                rlc_col.multiply(fabs(normal.dot(light_dir)));
                col.add(rlc_col);

                refracted.multiply(raytrace(transmitted_ray, cur_depth + 1));
                refracted.multiply(fabs(normal.dot(wt)));
                col.add(refracted);
            }

        // Normal n(sr.normal);
        // float cos_thetai = n * wo;
        // float eta = ior;    
            
        // if (cos_thetai < 0.0) {         // transmitted ray is outside     
        //     cos_thetai = -cos_thetai;
        //     n = -n;                     // reverse direction of normal
        //     eta = 1.0 / eta;            // invert ior 
        // }

        // float temp = 1.0 - (1.0 - cos_thetai * cos_thetai) / (eta * eta);
        // float cos_theta2 = sqrt(temp);
        // wt = -wo / eta - (cos_theta2 - cos_thetai / eta) * n;   
        
        // return (kt / (eta * eta) * white / fabs(sr.normal * wt));

        }

// end refract

    } else {
        // no object hit. return background color
        col.set(0.3, 0.3, 0.3, 1.0);
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