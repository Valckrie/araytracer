// point light source

#include <math.h>

#include "include/point_light.h"

// specified by a position and a colour

PointLight::PointLight(Vertex &p, Colour &i)
{
    point.x = p.x;
    point.y = p.y;
    point.z = p.z;
    point.w = 1.0;
    intensity.set(i.getRed(),i.getGreen(),i.getBlue(),i.getAlpha());
}

// provide the intensity and direction from which light arrives at given vertex

void PointLight::getLightProperties(Vertex &pos, Vector *ldir, Colour *i)
{
    *ldir = point.subtract(pos);
    ldir->normalise();

    // the direction is always the same (light is infinitely far away)
    // ldir->x = direction.x;
    // ldir->y = direction.y;
    // ldir->z = direction.z;

    // the intensity is always the same (not dependent on where it's going
    i->set(intensity.getRed(),intensity.getGreen(),intensity.getBlue(),intensity.getAlpha());

    if(attenuation == true) {
        Vector ld = point.subtract(pos);
        double mag = ld.magnitude();
        i->changeDivide(mag * mag);
        i->scaleLuminance(lum_scale*200);
    } else if(attenuation == false) {
        i->scaleLuminance(lum_scale);
    }
    
}

void PointLight::setLumScale(float ls) {
    lum_scale = ls;
}

void PointLight::setAttenuation(bool option) {
    attenuation = option;
}

bool PointLight::in_shadow(Ray& ray, Hit *hit) {
    // float t;
    // int numObjects = sr.w.objects.size();
    // float d = location.distance(ray.o);
                                                        
    // for (int j = 0; j < num_objects; j++)
    //     if (sr.w.objects[j]->shadow_hit(ray, t) && t < d)
    //         return (true); 
                                                        
    // return (false);     
}

Vertex PointLight::getLocation() {
    return point;
}