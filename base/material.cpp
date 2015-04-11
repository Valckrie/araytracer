#include <math.h>

#include "include/material.h"

Material::Material(void) {
    // gray matte
    ka.red = 0.3;
    ka.green = 0.3;
    ka.blue = 0.3;
    kd.red = 0.3;
    kd.green = 0.3;
    kd.blue =0.3;
    kr.red =  0.0;
    kr.green = 0.0;
    kr.blue = 0.0;
    ks.red = 0.0;
    ks.green =  0.0;
    ks.blue = 0.0;
    kt.red = 0.0;
    kt.green = 0.0;
    kt.blue = 0.0;
    n = 400.0;
    type = 0;
}

Material::Material(double R, double G, double B) {
    // specular RGB
    ka.red = R;
    ka.green = G;
    ka.blue = B;
    kd.red = R;
    kd.green = G;
    kd.blue = B;
    kr.red =  0.0;
    kr.green = 0.0;
    kr.blue = 0.0;
    ks.red = 0.5;
    ks.green =  0.5;
    ks.blue = 0.5;
    kt.red = 0.0;
    kt.green = 0.0;
    kt.blue = 0.0;
    n = 400.0;
    type = 1;
}

Material::Material(double R, double G, double B, double SPEC) {
    ka.red = R;
    ka.green = G;
    ka.blue = B;
    kd.red = R;
    kd.green = G;
    kd.blue = B;
    kr.red =  0.0;
    kr.green = 0.0;
    kr.blue = 0.0;
    ks.red = SPEC;
    ks.green =  SPEC;
    ks.blue = SPEC;
    kt.red = 0.0;
    kt.green = 0.0;
    kt.blue = 0.0;
    n = 400.0;
}

void Material::copySpecular() {
    ks.red = kd.red;
    ks.green =  kd.green;
    ks.blue = kd.blue;
}

Material::Material(int id) {
    switch(id) {
        case 1:
            // specular bronze
            ka.red = 0.2125;
            ka.green = 0.1275;
            ka.blue = 0.054;
            kd.red = 0.714;
            kd.green = 0.4284;
            kd.blue = 0.18144;
            kr.red =  0.0;
            kr.green = 0.0;
            kr.blue = 0.0;
            ks.red = 0.393548;
            ks.green =  0.271906;
            ks.blue = 0.166721;
            kt.red = 0.0;
            kt.green = 0.0;
            kt.blue = 0.0;
            type = 2;
        break;
        case 2:
            // reflective bronze
            ka.red = 0.2125;
            ka.green = 0.1275;
            ka.blue = 0.054;
            kd.red = 0.714;
            kd.green = 0.4284;
            kd.blue = 0.18144;
            kr.red =  0.393548;
            kr.green = 0.271906;
            kr.blue = 0.166721;
            ks.red = 0.393548;
            ks.green =  0.271906;
            ks.blue = 0.166721;
            kt.red = 0.0;
            kt.green = 0.0;
            kt.blue = 0.0;
            type = 3;
        break;
        case 3:
            // reflective
            ka.red = 0.3;
            ka.green = 0.3;
            ka.blue = 0.3;
            kd.red = 0.3;
            kd.green = 0.3;
            kd.blue =0.3;
            kr.red =  0.3;
            kr.green = 0.3;
            kr.blue = 0.3;
            ks.red = 0.0;
            ks.green =  0.0;
            ks.blue = 0.0;
            kt.red = 0.0;
            kt.green = 0.0;
            kt.blue = 0.0;
            n = 400.0;
            type = 3;
        break;
        case 4:             // silver
            ka.red = 0.19225;
            ka.green = 0.19225;
            ka.blue = 0.19225;
            kd.red = 0.50754 ;
            kd.green = 0.50754 ;
            kd.blue = 0.50754 ;
            kr.red =  0.508273;
            kr.green = 0.508273;
            kr.blue = 0.508273;
            ks.red = 0.508273;
            ks.green =  0.508273;
            ks.blue = 0.508273;
            kt.red = 0.0;
            kt.green = 0.0;
            kt.blue = 0.0;
            n = 400.0;
            type = 3;
        break;
        case 5:             // transp
            ka.red = 0.3;
            ka.green = 0.3;
            ka.blue = 0.3;
            kd.red = 0.3 ;
            kd.green = 0.3 ;
            kd.blue = 0.3 ;
            kr.red =  1.0;
            kr.green = 1.0;
            kr.blue = 1.0;
            ks.red = 0.50;
            ks.green =  0.50;
            ks.blue = 0.50;
            kt.red = 0.9;
            kt.green = 0.9;
            kt.blue = 0.9;
            n = 400.0;
            ior = 1;
            type = 4;
        break;
        case 99:             // checker
            float z = 0.5;
            ka.red = z;
            ka.green = z;
            ka.blue = z;
            kd.red = z;
            kd.green = z;
            kd.blue = z;
            kr.red =  0.0;
            kr.green = 0.0;
            kr.blue = 0.0;
            ks.red = 0.0;
            ks.green =  0.0;
            ks.blue = 0.0;
            kt.red = 0.0;
            kt.green = 0.0;
            kt.blue = 0.0;
            n = 400.0;
            type = 99;
        break;
    }
    n = 400.0;
}