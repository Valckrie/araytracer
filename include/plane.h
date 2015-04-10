#ifndef _Plane_H
#define _Plane_H

#include "include/object.h"

class Plane: public Object {
	public:
		Vertex point;
		Vector normal;
		Plane(void);
		Plane(Vertex p, Vector &n);
		Vector getNormal();
		Vertex getPoint();
		bool intersect(Ray &ray, Hit *h);
		bool shadow_hit(Ray &ray, float &tmin);

		static const double kEpsilon;   // for shadows and secondary rays
};

#endif