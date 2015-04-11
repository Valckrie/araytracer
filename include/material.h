#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "include/colour.h"

class Material {
    public:
    Colour ka;              // ambient component
    Colour kd;              // diffuse component
    Colour ks;              // specular component
    Colour kr;              // reflection
    Colour kt;              // transmission / refraction
    double n;
    double ior;
    int type;
    // 1 matte, 2 specular, 3 reflective, 4 transparent
    Material(void);
    Material(double R, double G, double B);
    Material(double R, double G, double B, double SPEC);
    void copySpecular();
    Material(int id);
};

#endif