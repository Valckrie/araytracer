#include "include/constants.h"
#include "include/triangle.h"

// default constructor

Triangle::Triangle (void) {
    v0 = Vertex(0, 0, 0, 1);
    v1 = Vertex(0, 0, 1, 1);
    v2 = Vertex(1, 0, 0, 1);
    normal = Vector(0, 1, 0);
}

// constructor

Triangle::Triangle (const Vertex& a, const Vertex& b, const Vertex& c) {
    v0 = a;
    v1 = b;
    v2 = c;
    compute_normal();
}

// compute_normal

void Triangle::compute_normal(void) {
    // normal = (v1 - v0) ^ (v2 - v0);
    normal = (v1.subtract(v0)).crossProduct(v2.subtract(v0));
    normal.normalise();
}

// intersection

bool Triangle::intersect(Ray& ray, Hit *hit) {   
    double a = v0.x - v1.x, b = v0.x - v2.x, c = ray.D.x, d = v0.x - ray.P.x; 
    double e = v0.y - v1.y, f = v0.y - v2.y, g = ray.D.y, h = v0.y - ray.P.y;
    double i = v0.z - v1.z, j = v0.z - v2.z, k = ray.D.z, l = v0.z - ray.P.z;
        
    double m = f * k - g * j, n = h * k - g * l, p = f * l - h * j;
    double q = g * i - e * k, s = e * j - f * i;
    
    double inv_denom  = 1.0 / (a * m + b * q + c * s);
    
    double e1 = d * m - b * n - c * p;
    double beta = e1 * inv_denom;
    
    if (beta < 0.0)
        return (false);
    
    double r = r = e * l - h * i;
    double e2 = a * n + d * q + c * r;
    double gamma = e2 * inv_denom;
    
    if (gamma < 0.0 )
        return (false);
    
    if (beta + gamma > 1.0)
        return (false);
            
    double e3 = a * p - b * r + d * s;
    double t = e3 * inv_denom;
    
    if (t < kEpsilon) 
        return (false);
        
    hit->obj = this;            
    hit->t = t;
    hit->n = normal;

    hit->p.x = ray.P.x  + t * ray.D.x;
    hit->p.y = ray.P.y  + t * ray.D.y;
    hit->p.z = ray.P.z  + t * ray.D.z;
    hit->p.w = 1.0;

    // sr.normal           = normal;   
    // sr.local_hit_point  = ray.o + t * ray.d;    
    
    return (true);  
}

// shadow_hit

// bool                                                                                         
// Triangle::shadow_hit(const Ray& ray, double& tmin) const {  
//     double a = v0.x - v1.x, b = v0.x - v2.x, c = ray.d.x, d = v0.x - ray.o.x; 
//     double e = v0.y - v1.y, f = v0.y - v2.y, g = ray.d.y, h = v0.y - ray.o.y;
//     double i = v0.z - v1.z, j = v0.z - v2.z, k = ray.d.z, l = v0.z - ray.o.z;
        
//     double m = f * k - g * j, n = h * k - g * l, p = f * l - h * j;
//     double q = g * i - e * k, s = e * j - f * i;
    
//     double inv_denom  = 1.0 / (a * m + b * q + c * s);
    
//     double e1 = d * m - b * n - c * p;
//     double beta = e1 * inv_denom;
    
//     if (beta < 0.0)
//         return (false);
    
//     double r = e * l - h * i;
//     double e2 = a * n + d * q + c * r;
//     double gamma = e2 * inv_denom;
    
//     if (gamma < 0.0)
//         return (false);
    
//     if (beta + gamma > 1.0)
//         return (false);
            
//     double e3 = a * p - b * r + d * s;
//     double t = e3 * inv_denom;
    
//     if (t < kEpsilon)
//         return (false);
                    
//     tmin = t;
    
//     return(true);   
// }  