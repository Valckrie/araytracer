#include <math.h>

#include "include/vector.h"

Vector::Vector()
{
  x = 0.0;
  y = 0.0;
  z = 0.0;
}

Vector::Vector (double i, double j, double k) {
  x = i;
  y = j;
  z = k;
}

void Vector::set(double px, double py, double pz)
{
  x = px;
  y = py;
  z = pz;
}

void Vector::set(Vector v)
{
  x = v.x;
  y = v.y;
  z = v.z;
}


void Vector::normalise(void)
{
  double l;

  l = x*x+y*y+z*z;
  l = sqrt(l);

  x = x/l;
  y = y/l;
  z = z/l;
}

double Vector::dot(const Vector &b)
{
  return (x*b.x)+(y*b.y)+(z*b.z);
}

Vector Vector::crossProduct(Vector v) {
    Vector t;
    t.set(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);
    return t;
}

Vector Vector::subtract (Vector v) {
    return Vector (x - v.x, y - v.y, z - v.z);
  }

Vector Vector::multiply (double scalar) {
    return Vector (x*scalar, y*scalar, z*scalar);
  }

Vector Vector::add (Vector v) {
  return Vector (x + v.x, y + v.y, z + v.z);
}

Vector Vector::negative () {
  return Vector (-x, -y, -z);
}

Vector operator* (const Matrix& mat, const Vector& v) {
  return (Vector(mat.m[0][0] * v.x + mat.m[0][1] * v.y + mat.m[0][2] * v.z,
                mat.m[1][0] * v.x + mat.m[1][1] * v.y + mat.m[1][2] * v.z,
                mat.m[2][0] * v.x + mat.m[2][1] * v.y + mat.m[2][2] * v.z));
}