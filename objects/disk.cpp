// Disk object

#include <math.h>

#include "include/disk.h"

// Disk defined as vertex point and normal

const double Disk::kEpsilon = 0.0001;

Disk::Disk(void) {
    centre = Vertex(0.0, 0.0, 0.0, 0.0);
    normal = Vector(0.0, 0.1, 0.0);
    radius = 1.0;
}

Disk::Disk(Vertex c, double r, Vector &n) {
    centre = c;
    radius = r;
    normal = n;
}

Vector Disk::getNormal() {
    return normal;
}

// Disk intersection test

bool Disk::intersect(Ray &ray, Hit *hit) {

    // float t = (point - ray.P) * normal / (ray.D * normal);
    float t = centre.subtract(ray.P).dot(normal) / ray.D.dot(normal);

    if (t <= kEpsilon)
        return (false);
        
    // Point3D p = ray.o + t * ray.d;
    Vertex p;
    p.x = ray.P.x  + t * ray.D.x;
    p.y = ray.P.y  + t * ray.D.y;
    p.z = ray.P.z  + t * ray.D.z;
    p.w = 1.0;

    double r_squared = radius * radius;

    if (centre.d_squared(p) < r_squared) {

        hit->obj = this;
        hit->t = t;
        hit->p = p;
        hit->n = normal;

        return (true);  
    }
    else
        return (false);
}

bool Disk::shadow_hit(Ray& ray, double &sh) {  
    // float t = (a - ray.o) * n / (ray.d * n);
    float t = centre.subtract(ray.P).dot(normal) / ray.D.dot(normal);

    if (t <= kEpsilon)
        return (false);
        
    // Point3D p = ray.o + t * ray.d;
    Vertex p;
    p.x = ray.P.x  + t * ray.D.x;
    p.y = ray.P.y  + t * ray.D.y;
    p.z = ray.P.z  + t * ray.D.z;
    p.w = 1.0;

    double r_squared = radius * radius;

    if (centre.d_squared(p) < r_squared) {
        sh = t;
        return (true);  
    }
    else
        return (false);
}