#ifndef _SCENE_H_
#define _SCENE_H_

#include "include/object.h"
#include "include/light.h"

class Scene {
  Object *scache;
  // obj_list is pointer to the object at the start of the object list
  Object *obj_list;

  Light  *light_list;
public:
  Scene(void);
  void addObject(Object &obj);
  void addLight(Light &light);
  Colour raytrace(Ray &ray, int level);
  bool shadowtrace(Ray &ray, double tlimit);
};

#endif
