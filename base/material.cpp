#include <math.h>

#include "include/material.h"

Material::Material(void) {
    ka.red = 0.3;
    ka.green = 0.3;
    ka.blue = 0.3;
    kd.red = 0.3;
    kd.green = 0.3;
    kd.blue =0.3;
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
}