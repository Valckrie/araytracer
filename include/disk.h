#ifndef _DISK_H
#define _DISK_H

#include "include/object.h"

class Disk: public Object {
	public:
		Vertex centre;
		Vector normal;
		double radius;
		Disk(void);
		Disk(Vertex c, double r, Vector &n);
		Vector getNormal();
		bool intersect(Ray &ray, Hit *h);
		bool shadow_hit(Ray &ray, double &sh);

		static const double kEpsilon;   // for shadows and secondary rays
};

#endif