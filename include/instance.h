#ifndef __INSTANCE__
#define __INSTANCE__

#include "include/object.h"
#include "include/matrix.h"

class Instance: public Object {	

    Object*           object_ptr;             // object to be transformed
    Matrix            inv_matrix;             // inverse transformation matrix
    static Matrix     forward_matrix;         // transformation matrix
    // BBox             bbox;                   // transformed object's bounding box
    // bool             transform_the_texture;  // do we transform the texture?

	public:
		Instance(void);   									
		
		Instance(Object* obj_ptr);					
		
		// Instance(const Instance& instance); 
		
		// virtual Instance* clone(void) const;				

		virtual ~Instance(void); 
		
		// Instance& operator= (const Instance& rhs);
				
		void set_object(Object* obj_ptr);	
				
		virtual Material* get_material(void) const;  								
				
		virtual void set_material(Material* materialPtr);
		
        //virtual		
		bool intersect(Ray& ray, Hit *hit);
		
		//
		bool shadow_hit(Ray &ray, double &sh);
		
		// affine tranformation functions
		
		void translate(const Vector& trans);
		
		void translate(const double dx, const double dy, const double dz);	
		
		void scale(const Vector& s);
		
		void scale(const double a, const double b, const double c);
		
		virtual void rotate_x(const double r);
		
		virtual void rotate_y(const double r);
		
		virtual void rotate_z(const double r);
		
		void shear(const Matrix& m);
		

};

#endif