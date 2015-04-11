// Plane object

#include <math.h>

#include "include/plane.h"

// Plane defined as vertex point and normal

const double Plane::kEpsilon = 0.0001;

Plane::Plane(void) {
    point = Vertex(0.0, 0.0, 0.0, 0.0);
    normal = Vector(0.0, 0.1, 0.0);
}

Plane::Plane(Vertex p, Vector &n) {
    point = p;
    normal = n;
}

Vector Plane::getNormal() {
    return normal;
}

Vertex Plane::getPoint() {
    return point;
}

// Plane intersection test

bool Plane::intersect(Ray &ray, Hit *hit) {

    // float t = (point - ray.P) * normal / (ray.D * normal);
    float t = point.subtract(ray.P).dot(normal) / ray.D.dot(normal);
                            
    // if (t > kEpsilon) {
    //     tmin = t;
    //     sr.normal = n;
    //     sr.local_hit_point = ray.o + t * ray.d;

    //     return (true);  
    // }

    if(t > kEpsilon) {

        hit->obj = this;
        hit->t = t;

        hit->p.x = ray.P.x  + t * ray.D.x;
        hit->p.y = ray.P.y  + t * ray.D.y;
        hit->p.z = ray.P.z  + t * ray.D.z;
        hit->p.w = 1.0;

        hit->n = normal;
        // hit->n.normalise();
        // not sure if this hit needs to be normalised. check later for shadows?
        return true;
    }
    return(false);
}

bool Plane::shadow_hit(Ray& ray, double &sh) {  
    // float t = (a - ray.o) * n / (ray.d * n);
    float t = point.subtract(ray.P).dot(normal) / ray.D.dot(normal);
                                
    if (t > kEpsilon) {
        sh = t;
        return (true);  
    }
    else
        return (false);
}