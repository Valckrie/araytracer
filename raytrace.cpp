#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <math.h>

#include "include/scene.h"
#include "include/sphere.h"
#include "include/directional_light.h"
#include "include/camera.h"
#include "include/plane.h"
#include "include/instance.h"

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
void addSphere(Scene *scene, Vertex &centre, float &rad, double R, double G, double B) {

    Sphere *s;
    Material *m;
    Vertex p;
    double ca, cr, cg, cb;

    s = new Sphere(centre, rad);

    cout << "x " << centre.x << " y " << centre.y << " z " << centre.z << " w " << centre.w;
    cout << "\n";
    cout << s->getRad();
    cout << "\n";

    // create new material with shared random Ka and Kd
    m = new Material();

    // cr = frand(); cg = frand(); cb = frand(); ca = frand();

    // cout << "red " << cr << " green " << cg << " blue " << cb << "\n";

    m->ka.red = R;
    m->ka.green = G;
    m->ka.blue = B;
    m->kd.red = R;
    m->kd.green = G;
    m->kd.blue = B;
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
    int samplesize = 16;
    int ss = (int)sqrt( (float)samplesize);
    Vertex samplepixel;

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
    Vertex sphere_location_2(0.3, 0.3, 0, 1);
    float sphere_radius_2 = 0.25;

    // in front
    Vertex sphere_location_3(-0.3, -0.3, 0, 1);
    float sphere_radius_3 = 0.25;

    // addSphere(scene, sphere_location_1, sphere_radius_1, 0.3, 0.3, 0.3);
    addSphere(scene, sphere_location_2, sphere_radius_2, 0.3, 0.7, 0.3);
    addSphere(scene, sphere_location_3, sphere_radius_3, 0.8, 0.2, 0.2);

    Material *grayMaterial = new Material();

    Sphere *sz;
    Vertex cz(-0.25, -0.25, -0.75, 1);
    float rz = 0.10;
    sz = new Sphere(cz, rz);
    sz->setMaterial(grayMaterial);
    scene->addObject(*sz);

    Plane *ground;
    Vertex ground_point(0, -5, 0, 1);
    Vector ground_normal(0, 1, 0);
    ground = new Plane(ground_point, ground_normal);
    ground->setMaterial(grayMaterial);
    scene->addObject(*ground);

    Plane *wall;
    Vertex wall_point(5, 0, 0, 1);
    Vector wall_normal(-1, 0, 0);
    wall = new Plane(wall_point, wall_normal);
    wall->setMaterial(grayMaterial);
    // scene->addObject(*wall);

    Vertex ellipse_c (0, 0, 0, 1);
    float ellipse_r = 0.5;
    Sphere* ellipse = new Sphere(ellipse_c, ellipse_r);
    ellipse->setMaterial(grayMaterial);

    Instance *eee = new Instance(ellipse);
    eee->scale(1, 2, 1);
    eee->rotate_x(-45);
    eee->translate(0, 0, 0);
    scene->addObject(*eee);

    // Instance* ellipse = new Instance(new Sphere(ellipse_c, ellipse_r));
    // ellipse->set_material(grayMaterial);
    // ellipse->scale(2, 3, 1);
    // ellipse->rotate_x(-45);
    // ellipse->translate(0, 1, 0);
    
    // scene->addObject(*ellipse);


    // Plane *wall2;
    // Vertex wall2_point(-5, 0, 0, 1);
    // Vector wall2_normal(1, 0, 0);
    // wall2 = new Plane(wall2_point, wall2_normal);
    // wall2->setMaterial(grayMaterial);
    // scene->addObject(*wall2);

    // for (int i = 0; i < 10; i++) {
    //     addSphere(scene, p1, rad1);
    // }

    Camera* cam = new Camera();
    cam->set_eye(0, 0, -4, 1);
    cam->set_lookat(0, 0, 0, 1);
    cam->compute_uvw();

    // RAYTRACE SCENE

    cout << "Sample size " << samplesize << "\n";
    cout << "Sqrt Ss " << ss << "\n";

    for(y = 0; y < YSIZE; y++) {                    // up main
        for(x = 0; x < XSIZE; x++) {                // across main

            Colour total;
            Colour avg;
            Colour sample;

            for(int i = 0; i < ss; i++) {           // up sample
                for(int j = 0; j < ss; j++) {       // across sample

                    samplepixel.x = (float)x - 0.5 * XSIZE + (j + 0.5) / ss;
                    samplepixel.x = (samplepixel.x / XSIZE);
                    samplepixel.y = (float)y - 0.5 * YSIZE + (i + 0.5) / ss;
                    samplepixel.y = (samplepixel.y / YSIZE);
                    // cout << "ss.x " << samplepixel.x;
                    // cout << " ss.y " << samplepixel.y << "\n";

                    Ray ray;

                    ray.P.set(cam->eye);
                    Vector ray_dir = cam->w.add(cam->u.multiply(samplepixel.x).add(cam->v.multiply(samplepixel.y)));
                    ray.D.set(ray_dir);
                    ray.D.normalise();

                    sample = scene->raytrace(ray,6);
                    total.add(sample);
                }
            }

            avg = total.divide(samplesize);
            
            // Ray ray;
            // double normalized_x = (((float)x)/XSIZE)-0.5;
            // double normalized_y = (((float)y)/YSIZE)-0.5;
            // cout << "norm x " << normalized_x;
            // cout << " norm y " << normalized_y << "\n";
            // Vector ray_dir = cam->w.add(cam->u.multiply(normalized_x).add(cam->v.multiply(normalized_y)));
            // ray.P.set(cam->eye);
            // ray.D.set(ray_dir);
            // ray.D.normalise();
            // avg = scene->raytrace(ray,6);
            // avg.add(avg);
            // avg = avg.divide(2);

            // Save result in frame buffer
            frame_buffer[y][x].red = avg.red;
            frame_buffer[y][x].green = avg.green;
            frame_buffer[y][x].blue = avg.blue;
        }
    }

    // OUTPUT IMAGE

    write_framebuffer();
}