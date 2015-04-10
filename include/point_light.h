#ifndef _POINT_LIGHT_H_
#define _POINT_LIGHT_H_

#include "include/light.h"
#include "include/ray.h"
#include "include/hit.h"

class PointLight: public Light {

	Vertex point;
	Vector direction;
    Colour intensity;
    float lum_scale;

    public:
        
        PointLight(Vertex &p, Colour &c);
        virtual void getLightProperties(Vertex &pos, Vector *ldir, Colour *i);
        void setLumScale(float ls);
        bool in_shadow(Ray &ray, Hit* hit);
};

#endif