#ifndef _VECTOR_H_
#define _VECTOR_H_

#include "include/matrix.h"

class Vector {
	public:
	double x;
	double y;
	double z;

	Vector(void);
    Vector(double x, double y, double z);

    void set(Vector v);
	void set(double x, double y, double z);
	void normalise(void);
	double dot(const Vector &b);
	double magnitude(void);
	Vector crossProduct(Vector v);
	Vector subtract (Vector v);
	Vector multiply (double scalar);
	Vector divide (double scalar);
	Vector add(Vector v);
	Vector negative();

	void normalMatrixCalc (const Matrix& mat);

};

Vector operator* (const Matrix& mat, const Vector& v);

#endif