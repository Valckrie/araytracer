#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "include/vertex.h"
#include "include/vector.h"
#include "include/colour.h"

class Light {
	Light *lt_next;
	bool shadows;

	public:
	// bool shadows;
		Light(void);
		void link(Light *light);
		Light *next(void);
		void turn_shadows(int option);
		
		bool cast_shadows();
		virtual void getLightProperties(Vertex &pos, Vector *ldir, Colour *i);
};

#endif