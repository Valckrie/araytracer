#include "include/camera.h"

// ----------------------------------------------------------------- default constructor

Camera::Camera() {
	eye.x = 0;
	eye.y = 0;
	eye.z = 500;
	eye.w = 1;
	lookat.x = 0;
	lookat.y = 0;
	lookat.z = 0;
	lookat.w = 1;
	up.set(0, 1, 0);
	u.set(1, 0, 0);
	v.set(0, 1, 0);
	w.set(0, 0, 1);
}

//-------------------------------------------------------------- compute_uvw

// This computes an orthornormal basis given the view point, lookat point, and up vector

void
Camera::compute_uvw(void) {
	// eye position - lookAt
	w = eye.subtract(lookat);
	// w = lookat.subtract(eye);
	// diffbtw
	w = w.negative();
	w.normalise();
	// w camdir, u camright, v camup
	u = up.crossProduct(w); 
	u.normalise();
	v = w.crossProduct(u);

	// take care of the singularity by hardwiring in specific camera orientations
	
	if (eye.x == lookat.x && eye.z == lookat.z && eye.y > lookat.y) { // camera looking vertically down
		u = Vector(0, 0, 1);
		v = Vector(1, 0, 0);
		w = Vector(0, 1, 0);	
	}
	
	if (eye.x == lookat.x && eye.z == lookat.z && eye.y < lookat.y) { // camera looking vertically up
		u = Vector(1, 0, 0);
		v = Vector(0, 0, 1);
		w = Vector(0, -1, 0);
	}
}



