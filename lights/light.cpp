// base class for lights

#include <math.h>

#include "include/light.h"

Light::Light(void)
{
}

void Light::link(Light *light)
{
  lt_next = light;
}

Light *Light::next(void)
{
  return lt_next;
}

void Light::turn_shadows(int option) {
	if(option == 1) {
		shadows = true;
	} else if(option == 0) {
		shadows = false;
	}
}

void Light::getLightProperties(Vertex &pos, Vector *ldir, Colour *intensity)
{
}

bool Light::cast_shadows() {
	return shadows;
}