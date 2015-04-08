#ifndef _VERTEX_H_
#define _VERTEX_H_

#include "include/vector.h"

class Vertex {
	public:
	double x;
	double y;
	double z;
	double w;
	Vertex(void);
	Vertex(double x, double y, double z, double w);
	void set(double x, double y, double z, double w);
	void set(Vertex v);
	Vector subtract (Vertex v);
};

#endif
