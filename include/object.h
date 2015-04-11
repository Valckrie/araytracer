#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <math.h>

#include "include/vertex.h"
#include "include/vector.h"
#include "include/colour.h"
#include "include/ray.h"
#include "include/hit.h"
#include "include/material.h"

class Object {
	Object *obj_next;
	public:
	Material *obj_mat;

	Object(void);
	void link(Object *obj);
	Object *next(void);
	void setMaterial(Material *m);
	Material* getMaterial(void);

	Colour getColour();

	// maybe needs to change
	virtual bool shadow_hit(Ray &ray, double &sh) { return false; }

	virtual bool intersect(Ray &ray, Hit *h) { return false; }
	virtual bool sintersect(Ray &ray, Hit *h, double tl);
};

#endif
