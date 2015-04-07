#ifndef __CAMERA__
#define __CAMERA__

#include "vertex.h"
#include "vector.h"

class Camera {
	public:
		Camera();   							// default constructor
		
		Vertex eye;				// eye point
		Vertex lookat; 			// lookat point				
		Vector u, v, w;			// orthonormal basis vectors
		Vector up;					// up vector
		
		void
		set_eye(const Vertex& p);

		void
		set_eye(const double x, const double y, const double z, const double w);
		
		void
		set_lookat(const Vertex& p);

		void
		set_lookat(const double x, const double y, const double z, const double w);

		void
		set_up_vector(const Vector& u);

		void
		set_up_vector(const double x, const double y, const double z);

		void									
		compute_uvw(void);
};

// inlined access functions

// ----------------------------------------------------------------- set_eye

inline void
Camera::set_eye(const Vertex& p) {
	eye = p;
}


// ----------------------------------------------------------------- set_eye

inline void
Camera::set_eye(const double x, const double y, const double z, const double w) {
	eye.x = x; eye.y = y; eye.z = z; eye.w = w;
}


// ----------------------------------------------------------------- set_lookat

inline void
Camera::set_lookat(const Vertex& p) {
	lookat = p;
}


// ----------------------------------------------------------------- set_lookat

inline void
Camera::set_lookat(const double x, const double y, const double z, const double w) {
	lookat.x = x; lookat.y = y; lookat.z = z; lookat.w = w;
}

// ----------------------------------------------------------------- set_up_vector

inline void
Camera::set_up_vector(const Vector& u) {
	up = u;
}

// ----------------------------------------------------------------- set_up_vector

inline void
Camera::set_up_vector(const double x, const double y, const double z) {
	up.x = x; up.y = y; up.z = z;
}

#endif