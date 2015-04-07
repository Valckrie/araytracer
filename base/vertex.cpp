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
