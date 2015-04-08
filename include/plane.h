#ifndef _Plane_H
#define _Plane_H

#include "include/object.h"

class Plane: public Object {
	public:
		Vector normal;
		Vertex point;
		Plane(void);
		Plane(Vector &n, Vertex p);
		Vector getNormal();
		Vertex getPoint();
		bool intersect(Ray &ray, Hit *h);

		static const double kEpsilon;   // for shadows and secondary rays
};

#endif