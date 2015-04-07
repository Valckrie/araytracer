#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "include/object.h"

class Sphere: public Object {
  Vertex centre;
  float  radius;
 public:
  Sphere(Vertex &c, float r);
  Vertex getCentre();
  float getRad();
  bool intersect(Ray &ray, Hit *h);
};

#endif
