#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>

#include "include/scene.h"
#include "include/sphere.h"
#include "include/directional_light.h"
#include "include/camera.h"

using namespace std;

#define XSIZE 512
#define YSIZE 512


Colour frame_buffer[YSIZE][XSIZE];

float frand()
{
  int x;
  float f;

  x = rand();
  f = (float)(x & 0xffff);
  f = f/65536.0;

  return f;
}

void write_framebuffer()
{
  FILE *f;
  f = fopen("out.ppm","w");

  int x, y;
  float r, g, b;

  fprintf(f, "P3\n%d %d\n255\n", XSIZE, YSIZE);

  for(y=YSIZE-1;y>=0;y-=1)
  {
    for(x=0;x<XSIZE;x+=1)
    {
      r = 255.0 * frame_buffer[y][x].getRed();
      g = 255.0 * frame_buffer[y][x].getGreen();
      b = 255.0 * frame_buffer[y][x].getBlue();
      if (r > 255.0) r = 255.0;
      if (g > 255.0) g = 255.0;
      if (b > 255.0) b = 255.0;
      fprintf(f, "%d %d %d\n",(int)r, (int)g, (int)b);
    }
  }

  fclose(f);
}

void clear_framebuffer()
{
  int x,y;

  for(y=0;y<YSIZE;y+=1)
  {
    for(x=0;x<XSIZE;x+=1)
    {
      frame_buffer[y][x].clear();
    }
  }
}


//
void addSphere(Scene *scene, Vertex &centre, float &rad) {

    Sphere *s;
    Material *m;
    Vertex p;
    double ca, cr, cg, cb;

    // position
    // p.set(frand()-0.5,frand()-0.5,frand()+1.0,1.0);
    // create with random radius
    // s = new Sphere(p, frand()/2.0);
    s = new Sphere(centre, rad);

    cout << "x " << centre.x << " y " << centre.y << " z " << centre.z << " w " << centre.w;
    cout << "\n";
    cout << s->getRad();
    cout << "\n";

    // create new material with shared random Ka and Kd
    m = new Material();

    cr = frand(); cg = frand(); cb = frand(); ca = frand();

    m->ka.red = cr * 0.1;
    m->ka.green = cg * 0.1;
    m->ka.blue = cb * 0.1;
    m->kd.red = cr * 0.5;
    m->kd.green = cg * 0.5;
    m->kd.blue = cb * 0.5;
    m->kr.red =  0.0;
    m->kr.green = 0.0;
    m->kr.blue = 0.0;
    m->ks.red = 0.5;
    m->ks.green =  0.5;
    m->ks.blue = 0.5;
    m->kt.red = 0.0;
    m->kt.green = 0.0;
    m->kt.blue = 0.0;
    m->n = 400.0;

    // set spheres material
    s->setMaterial(m);

    // as sphere to scene
    scene->addObject(*s);

}




// The main raytacing entry point.

int main(int argc, const char *argv[])
{
    Scene *scene;
    Vector v;
    int x,y;
    int n;
    DirectionalLight *dl;
    Colour cl;
    Vertex pp;
    double ca, cr, cg,cb;

    // srand(30115);
    srand(time(NULL));

    clear_framebuffer();

    // SETUP SCENE

    // Create a new scene to render
    scene = new Scene();

    // Create and add a directional light to the scene
    v.set(-1.0,-1.0,1.0);
    cl.set(1.0,1.0,1.0,1.0);
    pp.set(-50.0, 50.0, -48.25, 1.0);

    dl = new DirectionalLight(v, cl);

    scene->addLight(*dl);

    // origin
    Vertex sphere_location_1(0, 0, 0, 1);
    float sphere_radius_1 = 0.50;
    // in front
    Vertex sphere_location_2(0.25, 0.25, -0.5, 1);
    float sphere_radius_2 = 0.25;

    // in front
    Vertex sphere_location_3(-0.25, -0.25, -0.5, 1);
    float sphere_radius_3 = 0.25;

    addSphere(scene, sphere_location_1, sphere_radius_1);
    addSphere(scene, sphere_location_2, sphere_radius_2);
    addSphere(scene, sphere_location_3, sphere_radius_3);

    // for (int i = 0; i < 10; i++) {
    //     addSphere(scene, p1, rad1);
    // }



    Camera* cam = new Camera();
    // cam->set_eye(300,400,500,1);
    // cam->set_eye(1, 1, -2, 1);
    // cam->set_lookat(5, 5, -1000, 1);
    cam->set_eye(0, 0, -5, 1);
    cam->set_lookat(0, 0, 0, 1);
    cam->compute_uvw();


    // RAYTRACE SCENE

    for(y = 0; y < YSIZE; y++) {
        for(x = 0; x < XSIZE; x++) {

            Ray ray;
            float d;

            // Calculate a primary ray
            // d = 0.5;
            // ray.P.set(0.0,0.0,0.0,1.0);
            // ray.D.set((((float)x)/XSIZE)-0.5, (((float)y)/XSIZE)-0.5, d);
            // ray.D.normalise();

            // Vector image_point = normalized_x * cam->u + 
            //                     normalized_y * cam->v + 
            //                     cam->eye + cam->w;
            // Vector ray_direction = image_point - cam->eye;

            double normalized_x = (((float)x)/XSIZE)-0.5;
            double normalized_y = (((float)y)/YSIZE)-0.5;
            Vector ray_dir = cam->w.add(cam->u.multiply(normalized_x).add(cam->v.multiply(normalized_y)));
            ray.P.set(cam->eye);
            ray.D.set(ray_dir);
            ray.D.normalise();

            // Trace primary ray
            Colour col = scene->raytrace(ray,6);

            // Save result in frame buffer
            frame_buffer[y][x].red = col.red;
            frame_buffer[y][x].green = col.green;
            frame_buffer[y][x].blue = col.blue;
        }
    }

    // OUTPUT IMAGE

    write_framebuffer();
}