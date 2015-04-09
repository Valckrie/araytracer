OBJS = raytrace.o base/scene.o base/vector.o base/vertex.o base/colour.o objects/object.o objects/sphere.o base/material.o base/ray.o lights/light.o lights/directional_light.o base/hit.o base/camera.o objects/plane.o base/matrix.o objects/instance.o objects/triangle.o objects/opencylinder.o

raytrace: $(OBJS) 
	g++ -o raytrace $(OBJS) -lm

.cpp.o:
	g++ -c -O -I. $< -o $@

raytrace.o: include/scene.h include/sphere.h include/plane.h include/directional_light.h include/spot_light.h include/camera.h include/instance.h include/triangle.h

base/scene.o: include/scene.h

base/vector.o: include/vector.h

base/vertex.o: include/vertex.h

base/colour.o: include/colour.h

base/material.o: include/material.h

base/ray.o: include/ray.h

base/hit.o: include/hit.h

base/camera.o: include/camera.h

base/matrix.o: include/matrix.h

objects/object.o: include/object.h

objects/sphere.o: include/sphere.h

objects/plane.o: include/plane.h

objects/instance.o: include/instance.h

objects/triangle.o: include/triangle.h

objects/opencylinder.o: include/opencylinder.h

lights/light.o: include/light.h

lights/directional_light.o: include/directional_light.h

include/scene.h: include/object.h include/light.h
	touch include/scene.h

include/material.h: include/colour.h
	touch include/material.h

include/ray.h: include/vector.h include/vertex.h
	touch include/ray.h

include/hit.h: include/vector.h include/vertex.h
	touch include/hit.h

include/light.h: include/vector.h include/vertex.h include/ray.h include/colour.h
	touch include/light.h

include/directional_light.h: include/light.h
	touch include/directional_light.h

include/object.h: include/vector.h include/vertex.h include/ray.h include/colour.h include/material.h include/hit.h
	touch include/object.h

include/sphere.h: include/object.h
	touch include/sphere.h
	
include/camera.h: include/vector.h include/vertex.h
	touch include/camera.h
	
include/vertex.h: include/vector.h include/matrix.h
	touch include/vertex.h

include/vector.h: include/matrix.h
	touch include/vector.h
	
include/plane.h: include/object.h
	touch include/plane.h
	
include/triangle.h: include/object.h
	touch include/triangle.h

include/opencylinder.h: include/object.h
	touch include/opencylinder.h
	
include/instance.h: include/object.h include/matrix.h
	touch include/instance.h