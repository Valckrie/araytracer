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
    i->scaleLuminance(lum_scale);
}

void PointLight::setLumScale(float ls) {
    lum_scale = ls;
}


// Vector3D
// PointLight::get_direction(ShadeRec& sr) { 
//   return ((location - sr.hitPoint).hat());
// }