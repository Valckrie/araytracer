#include <math.h>
#include <iostream>

#include "include/scene.h"
#include "include/constants.h"
using namespace std;

const int MAX_DEPTH = 2;

Scene::Scene()
{
    scache = 0;
    obj_list = (Object *)0;
    light_list = (Light *)0;
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

    if (level > MAX_DEPTH) {
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

    col.clear();

    // if ray hit an object
    if (closest != (Object *)0) {
        // get light
        lt = light_list;

        Colour ocol;

        // get shading properties from material pointer
        Colour ka = closest->obj_mat->ka;
        Colour kd = closest->obj_mat->kd;
        Colour ks = closest->obj_mat->ks;
        Colour kr = closest->obj_mat->kr;
        Colour kt = closest->obj_mat->kt;
        double ior = closest->obj_mat->ior;
        int exponent = closest->obj_mat->exponent;
        int material_type = closest->obj_mat->type;
        Ray sray;

        // only for checker floor
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
            }
        }

        // regardless of light, ambient colour hack
        col.red     += ka.red;
        col.green   += ka.green;
        col.blue    += ka.blue;

        // loop through each light to calculate shading
        while (lt != (Light *)0) {
            Vector ldir;
            Vector xldir;
            Colour lcol;

            // set light properties
            lt->getLightProperties(position, &xldir, &lcol);
            xldir.normalise();

            // by default, not in a shadow
            bool in_shadow = false;
            Object *obj2;
            Vertex location = lt->getLocation();
            double shadowt;
            double d = location.distance(ray.P);       

// check for shadow intersections
            Ray shadowray(position, xldir);
            double shadowhit;

            if(lt->cast_shadows()) {
                obj2 = obj_list;
                while (obj2 != (Object *)0) {
                    if(obj2->shadow_hit(shadowray, shadowhit)) {
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

                // Diffuse component

                double dlc = xldir.dot(normal);
                if (dlc < 0.0) {
                    dlc = 0.0;
                }

                // Specular component

                Vector light_dir = xldir;
                Vector ray_dir_reversed = ray.D.negative();
                double normal_dot_light_dir = light_dir.dot(normal);

                // mirror reflection direction
                Vector r = light_dir.negative().add(normal.multiply(normal_dot_light_dir).multiply(2.0));
                
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
            }
            lt = lt->next(); // next light
        }

    // Reflected light
        // if ((kr.red > 0.0 || kr.green > 0.0 || kr.blue > 0.0) &&
        //     (kt.red == 0.0 && kt.green == 0.0 && kt.blue == 0.0)) {

        if(material_type == 3) {

            Vector ray_dir_reversed = ray.D.negative();
            Vector light_dir;
            double ndotrdr = normal.dot(ray_dir_reversed);

            light_dir = ray_dir_reversed.negative().add(normal.multiply(ndotrdr).multiply(2.0));

            double rlc = fabs(normal.dot(light_dir));
            Colour rlc_col = kr.returnDivide(rlc);

            // reflected ray offset by a small amount to avoid self reflection on surface
            Vertex adjust = position.addVector(normal.multiply(0.001));
            Ray reflected_ray(adjust, light_dir);

            double normal_dot_light_dir = light_dir.dot(normal);

            // recursively raytrace reflected ray
            rlc_col.multiply(raytrace(reflected_ray, cur_depth + 1));
            rlc_col.multiply(normal_dot_light_dir);
            
            // add component to colour
            col.add(rlc_col);
        }

    // End Reflect

    // Refracted light
        // if(kt.red > 0.0 || kt.green > 0.0 || kt.blue > 0.0) {

        if(material_type == 4) {

            Vector ray_dir_reversed = ray.D.negative();
            Vector light_dir;
            double ndotrdr = normal.dot(ray_dir_reversed);
            light_dir = ray_dir_reversed.negative().add(normal.multiply(ndotrdr).multiply(2.0));
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

        // total internal reflection
            double cos_thetai = normal.dot(ray_dir_reversed);
            // index of refraction
            double eta = ior;
            if(cos_thetai < 0.0) {
                eta = 1.0 / eta;
            }
            double temp = 1.0 - (1.0 - cos_thetai * cos_thetai) / (eta * eta);
            total_internal_reflection = temp < 0.0;
        // end tir

            if(total_internal_reflection == true) {
                // continued from above
                rlc_col.multiply(raytrace(reflected_ray, cur_depth + 1));
                col.add(rlc_col);
            } else {
                // tir is false
                Vector wt;
        // below is the sample_f return
                Vector n = normal;
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

                Vector tmp1 = ray_dir_reversed.negative().divide(eta);
                Vector tmp2 = n.multiply((cos_theta2 - cos_thetai / eta));
                wt = tmp1.subtract(tmp2);

                // transparency white by default
                Colour refracted (1.0, 1.0, 1.0, 1.0);
                double ktv = kt.red;
                double ttt = ktv / (eta * eta);
                refracted.changeDivide(fabs(normal.dot(wt)));
                refracted.multiply(ttt);
        // end samplef, return colour refracted
                Ray transmitted_ray(position, wt);

                // recursively trace reflected and refracted rays
                rlc_col.multiply(raytrace(reflected_ray, cur_depth + 1));
                rlc_col.multiply(fabs(normal.dot(light_dir)));
                col.add(rlc_col);

                refracted.multiply(raytrace(transmitted_ray, cur_depth + 1));
                refracted.multiply(fabs(normal.dot(wt)));
                col.add(refracted);
            }
        }

    // end refract

    } else {
        // no object hit. return background color
        // col.set(0.3, 0.3, 0.3, 1.0);
        col.set(0.4, 0.7, 1.0, 1.0);
    }
    // otherwise just return col, which is black, (bg col)
    return col;
}