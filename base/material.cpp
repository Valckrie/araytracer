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
            exponent = 55;
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
            exponent = 75;
            type = 3;
        break;
        case 5:             // glass internal
            ka.red = 0.0;
            ka.green = 0.0;
            ka.blue = 0.0;
            kd.red = 0.0;
            kd.green = 0.0;
            kd.blue = 0.0;
            kr.red =  1.0;
            kr.green = 1;
            kr.blue = 1;
            ks.red = 0.20;
            ks.green =  0.20;
            ks.blue = 0.20;
            kt.red = 0.9;
            kt.green = 0.9;
            kt.blue = 0.9;
            exponent = 2000;
            n = 400.0;
            ior = 0.75;
            type = 4;
        break;
        case 6:             // glass normal
            ka.red = 0.0;
            ka.green = 0.0;
            ka.blue = 0.0;
            kd.red = 0.0;
            kd.green = 0.0;
            kd.blue = 0.0;
            kr.red =  0.1;
            kr.green = .1;
            kr.blue = .1;
            ks.red = 0.20;
            ks.green =  0.20;
            ks.blue = 0.20;
            kt.red = 0.9;
            kt.green = 0.9;
            kt.blue = 0.9;
            exponent = 2000;
            n = 400.0;
            ior = 1.0;
            type = 4;
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