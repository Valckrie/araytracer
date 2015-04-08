// Plane object

#include <math.h>

#include "include/plane.h"

// Plane defined as vertex point and normal

const double Plane::kEpsilon = 0.000001;

Plane::Plane(void)
{
  normal = Vector(0.0, 0.1, 0.0);
  point = Vertex(0.0, 0.0, 0.0, 0.0);
}

Plane::Plane(Vector &n, Vertex p)
{
  normal = n;
  point = p;
}

Vector Plane::getNormal() {
  return normal;
}

Vertex Plane::getPoint() {
  return point;
}

// Plane intersection test

bool Plane::intersect(Ray &ray, Hit *hit) {

    float t = (point - ray.P) * normal / (ray.D * normal); 
                            
    if (t > kEpsilon) {
        tmin = t;
        sr.normal = n;
        sr.local_hit_point = ray.o + t * ray.d;

        return (true);  
    }

    return(false);
}