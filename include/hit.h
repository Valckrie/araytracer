#ifndef _HIT_H_
#define _HIT_H_

#include "include/vertex.h"
#include "include/vector.h"

class Object;

class Hit {
    public:
        Vertex p;               // point
        Vector n;               // normal
        double t;               // ray parameter
        Object *obj;            // obj

        int depth;              // depth
        Hit(void);
};

#endif