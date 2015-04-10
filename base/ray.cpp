#include "include/ray.h"

Ray::Ray(void) {
	
}

Ray::Ray(Vertex p, Vector d) {
	P = p;
	D = d;
}

Vertex Ray::position(double t)
{
  Vertex v;

  v.x = P.x + t * D.x;
  v.y = P.y + t * D.y;
  v.z = P.z + t * D.z;
  v.w = P.w;

  return v;
}