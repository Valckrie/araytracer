// Sphere object
#include <iostream>

#include <math.h>

#include "include/sphere.h"
#include "include/constants.h"
using namespace std;
// Sphere defined as vertex (in world space) and radius

const double Sphere::kEpsilon = 0.001;

Sphere::Sphere(Vertex &c, float r)
{
  centre = c;
  radius = r;
}

Vertex Sphere::getCentre() {
  return centre;
}

float Sphere::getRad() {
  return radius;
}

// Sphere intersection test

bool Sphere::intersect(Ray &ray, Hit *hit)
{
    // cout << "SPHERE INTERSECTING" << "\n";
    Vector ro;

    // offset ray by sphere position
    // equivalent to transforming ray into local sphere space

    // ro is temp ray origin by offset
    ro.set(ray.P.x-centre.x,ray.P.y-centre.y,ray.P.z-centre.z);

    float a = ray.D.dot(ray.D);
    float b = 2.0 * ray.D.dot(ro);
    float c = ro.dot(ro) - radius*radius;

    float disc = b*b - 4*a*c;

    if (disc < 0.0) {
        return false; // a negative value indicates no intersection.
    }
    // else all of below
    float ds = sqrtf(disc);
    float q;

    if (b < 0.0) {
        q = (-b - ds)/2.0;              // smaller root
    } else {
        q = (-b + ds)/2.0;              // larger root
    }

    float t0 = q/a;
    float t1 = c/q;

    if (t0>t1) {
        float temp = t0;
        t0 = t1;
        t1 = temp;
    }

    if (t1 < kEpsilon) {
        return false;
    }

    // if an intersection has been found, record details in hit object

    hit->obj = this;

    if (t0 < kEpsilon) {
        hit->t = t1;

        // hit->p.x = ray.P.x  + t1 * ray.D.x;
        // hit->p.y = ray.P.y  + t1 * ray.D.y;
        // hit->p.z = ray.P.z  + t1 * ray.D.z;
        // hit->p.w = 1.0;

        hit->p = ray.position(t1);

        hit->n.x = hit->p.x - centre.x;
        hit->n.y = hit->p.y - centre.y;
        hit->n.z = hit->p.z - centre.z;
        hit->n.normalise();

        return true;
    }

    hit->t = t0;

    // hit->p.x = ray.P.x  + t0 * ray.D.x;
    // hit->p.y = ray.P.y  + t0 * ray.D.y;
    // hit->p.z = ray.P.z  + t0 * ray.D.z;
    // hit->p.w = 1.0;

    hit->p = ray.position(t0);

    hit->n.x = hit->p.x - centre.x;
    hit->n.y = hit->p.y - centre.y;
    hit->n.z = hit->p.z - centre.z;
    hit->n.normalise();

    return true;
}

bool Sphere::shadow_hit(Ray &ray, double &sh) {
    // cout << "Sphere Shadow Hit" << "\n";
    Vector ro;

    ro.set(ray.P.x-centre.x,ray.P.y-centre.y,ray.P.z-centre.z);

    float a = ray.D.dot(ray.D);
    float b = 2.0 * ray.D.dot(ro);
    float c = ro.dot(ro) - radius*radius;

    float disc = b*b - 4*a*c;

    if (disc < 0.0) {
        return false; // a negative value indicates no intersection.
    }
    // else all of below
    float ds = sqrtf(disc);
    float q;

    if (b < 0.0) {
        q = (-b - ds)/2.0;              // smaller root
    } else {
        q = (-b + ds)/2.0;              // larger root
    }

    float t0 = q/a;
    float t1 = c/q;

    if (t0>t1) {
        float temp = t0;
        t0 = t1;
        t1 = temp;
    }

    if (t1 < kEpsilon) {
        return false;
    }

    // if an intersection has been found, record details in hit object

    if (t0 < kEpsilon) {

        // hit->t = t1;
        sh = t1;

        return true;
    } else {

        // hit->t = t0;
        sh = t0;

        return true;
    }
}