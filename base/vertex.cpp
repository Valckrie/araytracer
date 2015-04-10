#include <math.h>
#include "include/vertex.h"

Vertex::Vertex()
{
  x = 0.0;
  y = 0.0;
  z = 0.0;
  w = 0.0;
}

Vertex::Vertex(double px, double py, double pz, double pw)
{
  x = px;
  y = py;
  z = pz;
  w = pw;
}

Vertex::Vertex(double px, double py, double pz)
{
  x = px;
  y = py;
  z = pz;
  w = 1.0;
}

void Vertex::set(double px, double py, double pz, double pw)
{
  x = px;
  y = py;
  z = pz;
  w = pw;
}

void Vertex::set(Vertex v)
{
  x = v.x;
  y = v.y;
  z = v.z;
  w = v.w;
}

Vector Vertex::subtract (Vertex v) {
    return Vector(x - v.x, y - v.y, z - v.z);
}

Vector Vertex::add (Vertex v) {
    return Vector(x + v.x, y + v.y, z + v.z);
}

Vertex Vertex::addVector (Vector v) {
    return Vertex(x + v.x, y + v.y, z + v.z);
}

double Vertex::distance(Vertex& p) {
    return (sqrt(   (x - p.x) * (x - p.x) 
                +   (y - p.y) * (y - p.y)
                +   (z - p.z) * (z - p.z) ));
}

Vertex operator* (const Matrix& mat, const Vertex& p) {
	return (Vertex(mat.m[0][0] * p.x + mat.m[0][1] * p.y + mat.m[0][2] * p.z + mat.m[0][3],
					mat.m[1][0] * p.x + mat.m[1][1] * p.y + mat.m[1][2] * p.z + mat.m[1][3],
					mat.m[2][0] * p.x + mat.m[2][1] * p.y + mat.m[2][2] * p.z + mat.m[2][3],
					1.0));
}