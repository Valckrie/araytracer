#include <math.h>

#include "include/material.h"

Material::Material(void) {
    // gray matte
    ka.red = 0.2;
    ka.green = 0.2;
    ka.blue = 0.2;
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

Material::Material(double R, double G, double B, double A, double D, double S) {
    ka.red = R * A;
    ka.green = G * A;
    ka.blue = B * A;
    kd.red = R * D;
    kd.green = G * D;
    kd.blue = B * D;
    kr.red =  0.0;
    kr.green = 0.0;
    kr.blue = 0.0;
    ks.red = S;
    ks.green = S;
    ks.blue = S;
    kt.red = 0.0;
    kt.green = 0.0;
    kt.blue = 0.0;
    n = 400.0;
}

Material::Material(double R, double G, double B, double A, double D, double S, double F) {
    ka.red = R * A;
    ka.green = G * A;
    ka.blue = B * A;
    kd.red = R * D;
    kd.green = G * D;
    kd.blue = B * D;
    kr.red = F;// * R * S;
    kr.green = F;// * G * S;
    kr.blue = F;// * B * S;
    ks.red = R * S;
    ks.green = G * S;
    ks.blue = B * S;
    kt.red = 0.0;
    kt.green = 0.0;
    kt.blue = 0.0;
    n = 400.0;
    type = 3;
}

void Material::set_exp(int e) {
    exponent = e;
}
void Material::set_type(int t) {
    type = t;
}
void Material::set_ior(double iorval) {
    ior = iorval;
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
            //              jade
            ka.red = 0.135;
            ka.green = 0.2225;
            ka.blue = 0.1575;
            ka.alpha = 0.95;

            kd.red = 0.54;
            kd.green = 0.89;
            kd.blue = 0.63;
            kd.alpha = 0.95;

            kr.red = 0.316228;
            kr.green = 0.316228;
            kr.blue = 0.316228;

            ks.red = 0.316228;
            ks.green =  0.316228;
            ks.blue = 0.316228;
            ks.alpha = 0.95;

            kt.red = 0.0;
            kt.green = 0.0;
            kt.blue = 0.0;
            n = 400.0;
            exponent = 13;
            type = 3;
        break;
        case 4:             // silver reflective
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
            exponent = 51;
            type = 3;
        break;
        case 5:             // glass internal
            ka.red = 0.0;
            ka.green = 0.0;
            ka.blue = 0.0;
            kd.red = 0.4;
            kd.green = 0.7;
            kd.blue = 1.0;
            kr.red =  1;
            kr.green = 1;
            kr.blue = 1;
            ks.red = 0.10;
            ks.green = 0.10;
            ks.blue = 0.10;
            kt.red = 0.9;
            kt.green = 0.5;
            kt.blue = 0.5;
            exponent = 2000;
            n = 400.0;
            ior = 0.75;
            type = 4;
        break;
        case 6:             // glass normal
            ka.red = 0.0;
            ka.green = 0.0;
            ka.blue = 0.0;
            kd.red = 0.1;
            kd.green = 0.1;
            kd.blue = 0.1;
            kr.red =  0.1;
            kr.green = 0.1;
            kr.blue = 0.1;
            ks.red = 0.20;
            ks.green = 0.20;
            ks.blue = 0.20;
            kt.red = 0.9;
            kt.green = 0.9;
            kt.blue = 0.9;
            exponent = 2000;
            n = 400.0;
            ior = 1.0;
            type = 4;
        break;
        case 7:
            //              emerald
            ka.red = 0.0215;
            ka.green = 0.1745;
            ka.blue = 0.0215;
            ka.alpha = 0.55;

            kd.red = 0.07568;
            kd.green = 0.61424;
            kd.blue = 0.07568;
            kd.alpha = 0.55;

            kr.red = 0.633;
            kr.green = 0.727811;
            kr.blue = 0.633;

            ks.red = 0.633;
            ks.green =  0.727811;
            ks.blue = 0.633;
            ks.alpha = 0.55;

            kt.red = 0.0;
            kt.green = 0.0;
            kt.blue = 0.0;
            n = 400.0;
            exponent = 77;
            type = 2;
        break;
        case 8:
            //              pearl
            ka.red = 0.25;
            ka.green = 0.20725;
            ka.blue = 0.20725;
            ka.alpha = 0.922;

            kd.red = 1;
            kd.green = 0.829;
            kd.blue = 0.829;
            kd.alpha = 0.922;

            kr.red = 0.296648;
            kr.green = 0.296648;
            kr.blue = 0.296648;

            ks.red = 0.296648;
            ks.green = 0.296648;
            ks.blue = 0.296648;
            ks.alpha = 0.922;

            kt.red = 0.0;
            kt.green = 0.0;
            kt.blue = 0.0;
            n = 400.0;
            exponent = 12;
            type = 2;
        break;
        case 9:
            //              turquoise
            ka.red = 0.1;
            ka.green = 0.18725;
            ka.blue = 0.1745;
            ka.alpha = 0.8;

            kd.red = 0.396;
            kd.green = 0.74151;
            kd.blue = 0.69102;
            kd.alpha = 0.8;

            kr.red = 0.297254;
            kr.green = 0.30829;
            kr.blue = 0.306678;

            ks.red = 0.297254;
            ks.green = 0.30829;
            ks.blue = 0.306678;
            ks.alpha = 0.8;

            kt.red = 0.0;
            kt.green = 0.0;
            kt.blue = 0.0;
            n = 400.0;
            exponent = 13;
            type = 2;
        break;
        case 99:             // checker
            ka.red = 0.1;
            ka.green = 0.1;
            ka.blue = 0.1;
            kd.red = 0.8;
            kd.green = 0.8;
            kd.blue = 0.8;
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