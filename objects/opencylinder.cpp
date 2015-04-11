#include "include/opencylinder.h"
#include "include/constants.h"

// uses the value of kEpsilon defined in Constants.h

// default constructor

OpenCylinder::OpenCylinder(void) {
    y0 = -1.0;
    y1 = 1.0;
    radius = 1.0;
    inv_radius = 1.0;
}

// constructor

OpenCylinder::OpenCylinder(const double bottom, const double top, const double r) {
    y0 = bottom;
    y1 = top;
    radius = r;
    inv_radius = 1.0 / r;
}

// intersection 
// code reverses the normal when the ray hits the inside surface
// allows both sides to be shaded
// but completely messes up transparency.

bool OpenCylinder::intersect(Ray& ray, Hit *hit) {
                                                            
    double t;
    double ox = ray.P.x;
    double oy = ray.P.y;
    double oz = ray.P.z;
    double dx = ray.D.x;
    double dy = ray.D.y;
    double dz = ray.D.z;
    
    double a = dx * dx + dz * dz;   
    double b = 2.0 * (ox * dx + oz * dz);                   
    double c = ox * ox + oz * oz - radius * radius;
    double disc = b * b - 4.0 * a * c ;

            
    if (disc < 0.0)
        return(false);
    else {  
        double e = sqrt(disc);
        double denom = 2.0 * a;
        t = (-b - e) / denom;    // smaller root
        


        if (t > kEpsilon) {
            double yhit = oy + t * dy;
            
            if (yhit > y0 && yhit < y1) {


                // record object
                hit->obj = this;
                hit->t = t;

                hit->n = Vector((ox + t * dx) * inv_radius, 0.0, (oz + t * dz) * inv_radius);
                // sr.normal = Normal((ox + t * dx) * inv_radius, 0.0, (oz + t * dz) * inv_radius);
                
                // test for hitting from inside

                if ( (ray.D.negative()).dot(hit->n) < 0.0 ) hit->n.negative();
                // if (-ray.d * sr.normal < 0.0) sr.normal = -sr.normal;
                
                // sr.local_hit_point = ray.o + t * ray.d;
                hit->p.x = ray.P.x + t * ray.D.x;
                hit->p.y = ray.P.y + t * ray.D.y;
                hit->p.z = ray.P.z + t * ray.D.z;
                hit->p.w = 1.0;
                
                return (true);
            }
        } 
        
        t = (-b + e) / denom;    // larger root
        
        if (t > kEpsilon) {
            double yhit = oy + t * dy;
            
            if (yhit > y0 && yhit < y1) {

                // record object
                hit->obj = this;
                hit->t = t;

                // sr.normal = Normal((ox + t * dx) * inv_radius, 0.0, (oz + t * dz) * inv_radius);
                hit->n = Vector((ox + t * dx) * inv_radius, 0.0, (oz + t * dz) * inv_radius);
                
                // test for hitting inside surface
            
                if ( (ray.D.negative()).dot(hit->n) < 0.0 ) hit->n.negative();

                // if (-ray.d * sr.normal < 0.0)
                //     sr.normal = -sr.normal;
                    
                // sr.local_hit_point = ray.o + t * ray.d;
                hit->p.x = ray.P.x + t * ray.D.x;
                hit->p.y = ray.P.y + t * ray.D.y;
                hit->p.z = ray.P.z + t * ray.D.z;
                hit->p.w = 1.0;
    
                return (true);
            }
        } 
    }
    
    return (false);         
}

bool OpenCylinder::shadow_hit(Ray& ray, double &sh) {
                                                            
    double t;
    double ox = ray.P.x;
    double oy = ray.P.y;
    double oz = ray.P.z;
    double dx = ray.D.x;
    double dy = ray.D.y;
    double dz = ray.D.z;
    
    double a = dx * dx + dz * dz;   
    double b = 2.0 * (ox * dx + oz * dz);                   
    double c = ox * ox + oz * oz - radius * radius;
    double disc = b * b - 4.0 * a * c ;

            
    if (disc < 0.0)
        return(false);
    else {  
        double e = sqrt(disc);
        double denom = 2.0 * a;
        t = (-b - e) / denom;    // smaller root
        


        if (t > kEpsilon) {
            double yhit = oy + t * dy;
            
            if (yhit > y0 && yhit < y1) {

                // record object
                sh = t;
                
                return (true);
            }
        } 
        
        t = (-b + e) / denom;    // larger root
        
        if (t > kEpsilon) {
            double yhit = oy + t * dy;
            
            if (yhit > y0 && yhit < y1) {

                // record object
                sh = t;
                return (true);
            }
        } 
    }
    
    return (false);         
}