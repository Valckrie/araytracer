#ifndef __TRIANGLE__
#define __TRIANGLE__

#include "include/object.h"

class Triangle: public Object {  

    Vertex v0, v1, v2;
    Vector normal;

    public:
        Triangle(void);                                                 
                
        Triangle(const Vertex& a, const Vertex& b, const Vertex& c);

        void compute_normal(void);
        
        bool intersect(Ray& ray, Hit *hit);                           
        
        bool shadow_hit(Ray& ray, double& sh); 
};

#endif