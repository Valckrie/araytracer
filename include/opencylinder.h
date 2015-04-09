#ifndef __OPEN_CYLINDER__
#define __OPEN_CYLINDER__

// open cylinder is defined by its extent in the y direction and its radius.
// centered on the y axis.

#include "include/object.h"

class OpenCylinder: public Object {
    
    double      y0;             // bottom y value
    double      y1;             // top y value
    double      radius;         // radius
    double      inv_radius;     // one over the radius  

    public:
        OpenCylinder(void);                                     

        OpenCylinder(const double bottom, const double top, const double radius);
                        
        bool intersect(Ray& ray, Hit *hit);
        
        
};

#endif