#include "include/constants.h"
#include "include/instance.h"
#include <iostream>
using namespace std;
// initialise the static transformation matrix

Matrix Instance::forward_matrix;

// ----------------------------------------------------------------  default constructor

Instance::Instance(void) {
 //    Object();
 //    object_ptr(NULL);
 //    // inv_matrix();
 //    inv_matrix = new Matrix();
	// forward_matrix.set_identity();
}


// ----------------------------------------------------------------  constructor

Instance::Instance(Object* obj_ptr) {
    // cout << "MADE INSTANCE" << "\n";
    // Object();
    object_ptr = obj_ptr;
    // inv_matrix();
    // inv_matrix = new Matrix();
    forward_matrix.set_identity();
}

// ---------------------------------------------------------------- copy constructor

// Instance::Instance (const Instance& instance)
// 	: 	Object(instance),
// 		inv_matrix(instance.inv_matrix),
// {
// 	if(instance.object_ptr)
// 		object_ptr = instance.object_ptr->clone(); 
// 	else  object_ptr = NULL;
// }


// ---------------------------------------------------------------- clone

// Instance* 
// Instance::clone(void) const {
// 	return (new Instance(*this));
// }


// ---------------------------------------------------------------- destructor

Instance::~Instance(void) {
	if (object_ptr) {
		delete object_ptr;
		object_ptr = NULL;
	}
}


// ---------------------------------------------------------------- assignment operator

// Instance& 
// Instance::operator= (const Instance& rhs) {
// 	if (this == &rhs)
// 		return (*this);

// 	Object::operator=(rhs);
		
// 	if(object_ptr) {
// 		delete object_ptr;
// 		object_ptr = NULL;
// 	}
	
// 	if (rhs.object_ptr)
// 		object_ptr = rhs.object_ptr->clone();
// 	else
// 		object_ptr = NULL;
	
// 	inv_matrix				= rhs.inv_matrix;

// 	return (*this);
// }


//------------------------------------------------------------------ set_object

void 												
Instance::set_object(Object* obj_ptr) {
	object_ptr = obj_ptr;
}

//---------------------------------------------------------------- get_material
																
Material* 
Instance::get_material(void) const {
	return (obj_mat);     
}


//---------------------------------------------------------------- set_material
// Here, obj_mat is Object::obj_mat

void 
Instance::set_material(Material* m_ptr) {
	obj_mat = m_ptr;
}



//----------------------------------------------------------------------------------------- hit 

bool 												 
Instance::intersect(Ray& ray, Hit *hit) {
	
    // cout << "INSTANCE HITTING" << "\n";
    // copy ray to new inverted ray
    Ray inv_ray = ray;  

    // inverse ray origin = inv matrix dot product original ray origin
	inv_ray.P = inv_matrix * inv_ray.P;   
	inv_ray.D = inv_matrix * inv_ray.D;
				
	if (object_ptr->intersect(inv_ray, hit)) {

        // hit->n = inv_matrix * hit->n;
        // hit->n = hit->n.normalMatrixCalc(inv_matrix, hit->n);
        hit->obj = this;
        // dont know if need this? object pointer ref ^
        hit->n.normalMatrixCalc(inv_matrix);
        hit->n.normalise();

		// sr.normal = inv_matrix * sr.normal;
		// sr.normal.normalize();				
						
		if (object_ptr->getMaterial())
			obj_mat = object_ptr->getMaterial(); 
			
		// if (!transform_the_texture) 

            hit->p.x = ray.P.x  + hit->t * ray.D.x;
            hit->p.y = ray.P.y  + hit->t * ray.D.y;
            hit->p.z = ray.P.z  + hit->t * ray.D.z;
            hit->p.w = 1.0;

			// sr.local_hit_point = ray.o + t * ray.d;  		 

		return (true);
	} 

	return (false);   
}


//-------------------------------------------------------------------------------- scale

void 
Instance::scale(const Vector& s) {

	Matrix	inv_scaling_matrix;			// temporary inverse scaling matrix
	
	inv_scaling_matrix.m[0][0] = 1.0 / s.x;
	inv_scaling_matrix.m[1][1] = 1.0 / s.y;
	inv_scaling_matrix.m[2][2] = 1.0 / s.z;

	inv_matrix = inv_matrix * inv_scaling_matrix;			

	Matrix	scaling_matrix;				// temporary scaling matrix
	
	scaling_matrix.m[0][0] = s.x;
	scaling_matrix.m[1][1] = s.y;
	scaling_matrix.m[2][2] = s.z;
	
	forward_matrix = scaling_matrix * forward_matrix; 		
}


//-------------------------------------------------------------------------------- scale

void 
Instance::scale(const double a, const double b, const double c) {

	Matrix inv_scaling_matrix;					// temporary inverse scaling matrix
	
	inv_scaling_matrix.m[0][0] = 1.0 / a;
	inv_scaling_matrix.m[1][1] = 1.0 / b;
	inv_scaling_matrix.m[2][2] = 1.0 / c;
	
	inv_matrix = inv_matrix * inv_scaling_matrix;			

	Matrix scaling_matrix;						// temporary scaling matrix
	
	scaling_matrix.m[0][0] = a;
	scaling_matrix.m[1][1] = b;
	scaling_matrix.m[2][2] = c;
	
	forward_matrix = scaling_matrix * forward_matrix; 	
}


//-------------------------------------------------------------------------------- translate

void
Instance::translate(const Vector& trans) {

	Matrix inv_translation_matrix;				// temporary inverse translation matrix	
			
	inv_translation_matrix.m[0][3] = -trans.x;
	inv_translation_matrix.m[1][3] = -trans.y;
	inv_translation_matrix.m[2][3] = -trans.z;
					
	inv_matrix = inv_matrix * inv_translation_matrix;
	
	Matrix translation_matrix;					// temporary translation matrix	
	
	translation_matrix.m[0][3] = trans.x;
	translation_matrix.m[1][3] = trans.y;
	translation_matrix.m[2][3] = trans.z;
	
	forward_matrix = translation_matrix * forward_matrix; 
}


//-------------------------------------------------------------------------------- translate

void
Instance::translate(const double dx, const double dy, const double dz) {

	Matrix inv_translation_matrix;				// temporary inverse translation matrix	
			
	inv_translation_matrix.m[0][3] = -dx;
	inv_translation_matrix.m[1][3] = -dy;
	inv_translation_matrix.m[2][3] = -dz;
					
	inv_matrix = inv_matrix * inv_translation_matrix;
	
	Matrix translation_matrix;					// temporary translation matrix	
	
	translation_matrix.m[0][3] = dx;
	translation_matrix.m[1][3] = dy;
	translation_matrix.m[2][3] = dz;
	
	forward_matrix = translation_matrix * forward_matrix; 
}



//-------------------------------------------------------------------------------- rotate_x

void
Instance::rotate_x(const double theta) {

	double sin_theta = sin(theta * PI_ON_180);
	double cos_theta = cos(theta * PI_ON_180);
	
	Matrix inv_x_rotation_matrix;					// temporary inverse rotation matrix about x axis
	
	inv_x_rotation_matrix.m[1][1] = cos_theta;
	inv_x_rotation_matrix.m[1][2] = sin_theta;   	
	inv_x_rotation_matrix.m[2][1] = -sin_theta;  
	inv_x_rotation_matrix.m[2][2] = cos_theta;		
					
	inv_matrix = inv_matrix * inv_x_rotation_matrix;	   	
	
	Matrix x_rotation_matrix;						// temporary rotation matrix about x axis
	
	x_rotation_matrix.m[1][1] = cos_theta;
	x_rotation_matrix.m[1][2] = -sin_theta;
	x_rotation_matrix.m[2][1] = sin_theta;
	x_rotation_matrix.m[2][2] = cos_theta;
				
	forward_matrix = x_rotation_matrix * forward_matrix; 
}


//-------------------------------------------------------------------------------- rotate_y

void
Instance::rotate_y(const double theta) {

	double sin_theta = sin(theta * PI / 180.0);
	double cos_theta = cos(theta * PI / 180.0);

	Matrix inv_y_rotation_matrix;					// temporary inverse rotation matrix about y axis
	
	inv_y_rotation_matrix.m[0][0] = cos_theta;   
	inv_y_rotation_matrix.m[0][2] = -sin_theta;  
	inv_y_rotation_matrix.m[2][0] = sin_theta;
	inv_y_rotation_matrix.m[2][2] = cos_theta;		
					
	inv_matrix = inv_matrix * inv_y_rotation_matrix;	   	
	
	Matrix y_rotation_matrix;						// temporary rotation matrix about x axis
	
	y_rotation_matrix.m[0][0] = cos_theta;
	y_rotation_matrix.m[0][2] = sin_theta;
	y_rotation_matrix.m[2][0] = -sin_theta;
	y_rotation_matrix.m[2][2] = cos_theta;
				
	forward_matrix = y_rotation_matrix * forward_matrix; 
}



//-------------------------------------------------------------------------------- rotate_z

void
Instance::rotate_z(const double theta) {
	double sin_theta = sin(theta * PI / 180.0);
	double cos_theta = cos(theta * PI / 180.0);

	Matrix inv_z_rotation_matrix;					// temporary inverse rotation matrix about y axis	
	
	inv_z_rotation_matrix.m[0][0] = cos_theta;
	inv_z_rotation_matrix.m[0][1] = sin_theta;   	
	inv_z_rotation_matrix.m[1][0] = -sin_theta;  
	inv_z_rotation_matrix.m[1][1] = cos_theta;	
					
	inv_matrix = inv_matrix * inv_z_rotation_matrix;
	
	Matrix z_rotation_matrix;						// temporary rotation matrix about y axis
	
	z_rotation_matrix.m[0][0] = cos_theta;
	z_rotation_matrix.m[0][1] = -sin_theta;
	z_rotation_matrix.m[1][0] = sin_theta;
	z_rotation_matrix.m[1][1] = cos_theta;
				
	forward_matrix = z_rotation_matrix * forward_matrix; 
}


//-------------------------------------------------------------------------------- shear

void												
Instance::shear(const Matrix& s) {
	
	Matrix inverse_shearing_matrix;    // inverse shear matrix
	
	// discriminant

	double d = 1.0 	- s.m[1][0] * s.m[0][1] - s.m[2][0] * s.m[0][2]  - s.m[2][1] * s.m[1][2]
					+ s.m[1][0] * s.m[2][1] * s.m[0][2] + s.m[2][0] * s.m[0][1] * s.m[2][1];
					
	// diagonals
	
	inverse_shearing_matrix.m[0][0] = 1.0 - s.m[2][1] * s.m[1][2];
	inverse_shearing_matrix.m[1][1] = 1.0 - s.m[2][0] * s.m[0][2];
	inverse_shearing_matrix.m[2][2] = 1.0 - s.m[1][0] * s.m[0][1];
	inverse_shearing_matrix.m[3][3] = d;
	
	// first row
	
	inverse_shearing_matrix.m[0][1] = -s.m[1][0] + s.m[2][0] * s.m[1][2];
	inverse_shearing_matrix.m[0][2] = -s.m[2][0] + s.m[1][0] * s.m[2][1];
	
	// second row
	
	inverse_shearing_matrix.m[1][0] = -s.m[0][1] + s.m[2][1] * s.m[0][2];
	inverse_shearing_matrix.m[1][2] = -s.m[2][1] + s.m[2][0] * s.m[0][1];
	
	// third row
	
	inverse_shearing_matrix.m[2][0] = -s.m[0][2] + s.m[0][1] * s.m[1][2];
	inverse_shearing_matrix.m[2][1] = -s.m[1][2] + s.m[1][0] * s.m[0][2] ;
	
	// divide by discriminant
	
	inverse_shearing_matrix = inverse_shearing_matrix / d;
	
	inv_matrix = inv_matrix * inverse_shearing_matrix;	
	
	forward_matrix = s * forward_matrix; 
}