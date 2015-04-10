#ifndef _VERTEX_H_
#define _VERTEX_H_

#include "include/vector.h"
#include "include/matrix.h"

class Vertex {
	public:
	double x;
	double y;
	double z;
	double w;
	Vertex(void);
	Vertex(double x, double y, double z, double w);
	Vertex(double x, double y, double z);
	void set(double x, double y, double z, double w);
	void set(Vertex v);
	Vector subtract (Vertex v);
	Vector add (Vertex v);
	Vertex addVector (Vector v);
	double distance(Vertex &p);
};

Vertex operator* (const Matrix& mat, const Vertex& p);

#endif