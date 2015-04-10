#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <math.h>

#include "include/scene.h"
#include "include/sphere.h"
#include "include/directional_light.h"
#include "include/point_light.h"
#include "include/camera.h"
#include "include/plane.h"
#include "include/instance.h"
#include "include/triangle.h"
#include "include/opencylinder.h"

using namespace std;

#define XSIZE 640
#define YSIZE 480

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

    // cout << "x " << centre.x << " y " << centre.y << " z " << centre.z << " w " << centre.w;
    // cout << "\n";
    // cout << s->getRad();
    // cout << "\n";

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
    int x,y;
    // int n;

    int samplesize = 1;
    int ss = (int)sqrt( (float)samplesize);
    Vertex samplepixel;

    // srand(30115);
    srand(time(NULL));

    clear_framebuffer();

    // SETUP SCENE

    // Create a new scene to render
    scene = new Scene();

    Colour col_white;
    col_white.set(1.0,1.0,1.0,1.0);

    Camera* cam = new Camera();
    cam->set_eye(0, 10, 25, 1);
    cam->set_lookat(0, 5, 0, 1);
    cam->compute_uvw();

    // Create and add a directional light to the scene
    Vector dir_light_dir(-1.0, -1.0, 0.0);
    DirectionalLight *dir_light1 = new DirectionalLight(dir_light_dir, col_white);
    // scene->addLight(*dir_light1);

    // POINT LIGHT
    Vertex point_light_pos (10, 10, 0, 1.0);
    PointLight *pt_light1 = new PointLight(point_light_pos, col_white);
    pt_light1->setLumScale(2.0);
    pt_light1->turn_shadows(1);
    scene->addLight(*pt_light1);

    // POINT LIGHT SPHERE MARKER
    float marker_radius = 0.5;
    // addSphere(scene, point_light_pos, marker_radius, 1.0, 1.0, 1.0);
    
    Vertex testpos (0, 5, 0, 1.0);
    float test = 3;
    addSphere(scene, testpos, test, 0.8, 0.1, 0.3);

    Vertex testpos2 (2, 2, 0, 1.0);
    float test2 = 1;
    addSphere(scene, testpos2, test2, 0.5, 0.5, 0.5);


    Material *grayMaterial = new Material();
    Material *newMaterial = new Material(0.2, 0.8, 0.4);
    Material *specR = new Material(0.8, 0.2, 0.2, 1.0);
    Material *specG = new Material(0.2, 0.8, 0.2, 0.8);
    Material *specB = new Material(0.2, 0.2, 0.8, 0.6);
    specB->copySpecular();
    Material *matteB = new Material(0.2, 0.2, 0.8, 0.0);
    Material *matteG = new Material(0.2, 0.2, 0.8, 0.0);
    Material *bronze = new Material(1);
    Material *bronzeR = new Material(2);

    Plane *ground;
    Vertex ground_point(0, -5, 0, 1);
    Vector ground_normal(0, 1, 0);
    ground = new Plane(ground_point, ground_normal);
    ground->setMaterial(grayMaterial);
    scene->addObject(*ground);



    Vertex ellipse_c (0, 0, 0, 1);
    float ellipse_r = 1;
    Sphere* ellipse = new Sphere(ellipse_c, ellipse_r);
    ellipse->setMaterial(grayMaterial);

    Sphere* sphereGreen = new Sphere(ellipse_c, ellipse_r);
    sphereGreen->setMaterial(specG);

    Sphere* sphereSpec = new Sphere(ellipse_c, ellipse_r);
    sphereSpec->setMaterial(newMaterial);

    Sphere* sphereRed = new Sphere(ellipse_c, ellipse_r);
    sphereRed->setMaterial(specR);

    Sphere* sphereBlue = new Sphere(ellipse_c, ellipse_r);
    sphereBlue->setMaterial(specB);

    Sphere* sphBrz = new Sphere(ellipse_c, ellipse_r);
    sphBrz->setMaterial(bronzeR);

    Instance *e1 = new Instance(sphBrz);
    e1->scale(2.5, 2.5, 2.5);
    e1->rotate_y(0);
    e1->translate(0, -3.5, 0);
    scene->addObject(*e1);

    Instance *sphgray = new Instance(ellipse);
    sphgray->scale(2.5, 2.5, 2.5);
    sphgray->rotate_y(0);
    sphgray->translate(7, -3.5, 0);
    scene->addObject(*sphgray);

    Instance *e2 = new Instance(ellipse);
    e2->scale(2.3, 2.3, 2.3);
    e2->rotate_y(0);
    e2->translate(5, 0, -15);
    scene->addObject(*e2);

    Instance *e3 = new Instance(sphereSpec);
    e3->scale(2, 2, 2);
    e3->rotate_y(0);
    e3->translate(5, 1, 4.2);
    scene->addObject(*e3);

    Instance *e4 = new Instance(sphereRed);
    e4->scale(1.5, 1.5, 1.5);
    e4->rotate_y(0);
    e4->translate(7, -4, 6);
    scene->addObject(*e4);   

    Instance *e5 = new Instance(sphereBlue);
    e5->scale(1.5, 1.5, 1.5);
    e5->rotate_y(0);
    e5->translate(0, -5, 0);
    scene->addObject(*e5);

    Instance *e6 = new Instance(sphereGreen);
    e6->scale(1.5, 1.5, 1.5);
    e6->rotate_y(0);
    e6->translate(0, 0, 0);
    scene->addObject(*e6);

    Instance *e7 = new Instance(sphereBlue);
    e7->scale(1.5, 1.5, 1.5);
    e7->rotate_y(0);
    e7->translate(-7, -5, 6);
    scene->addObject(*e7);

    // Triangle *triangle1 = new Triangle(Vertex(-5, 10, 1), Vertex(0, 15, 1), Vertex(5, 10, 1));
    // triangle1->setMaterial(newMaterial);

    // Instance *tri1 = new Instance(triangle1);
    // tri1->rotate_z(0);
    // tri1->translate(0, 0, 0);
    // scene->addObject(*tri1);

    OpenCylinder *opencylinder1 = new OpenCylinder(0, 1, 2.2);
    opencylinder1->setMaterial(newMaterial);

    Instance *oc1 = new Instance(opencylinder1);
    // oc1->rotate_z(-60);
    // oc1->rotate_y(-60);
    oc1->scale(1, 8.5, 1);
    oc1->translate(-5, -5, -5);
    scene->addObject(*oc1);

    // for (int i = 0; i < 10; i++) {
    //     addSphere(scene, p1, rad1);
    // }



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

                // pp.x = vp.s * (c - 0.5 * vp.hres + (q + 0.5) / n); 
                // pp.y = vp.s * (r - 0.5 * vp.vres + (p + 0.5) / n);




                    samplepixel.x = (float)x - 0.5 * XSIZE + (j + 0.5) / ss;
                    samplepixel.x = (samplepixel.x / XSIZE);
                    samplepixel.y = (float)y - 0.5 * XSIZE + (i + 0.5) / ss;
                    samplepixel.y = (samplepixel.y / XSIZE);
                    
                    // samplepixel.x = ((float)x/XSIZE) - 0.5 * XSIZE + (j + 0.5) / ss;
                    // samplepixel.y = ((float)y/YSIZE) - 0.5 * YSIZE + (i + 0.5) / ss;

                    // cout << "ss.x " << samplepixel.x;
                    // cout << " ss.y " << samplepixel.y << "\n";

                    Ray ray;

                    ray.P.set(cam->eye);
                    Vector ray_dir = cam->w.add(cam->u.multiply(samplepixel.x).add(cam->v.multiply(samplepixel.y)));
                    ray.D.set(ray_dir);
                    ray.D.normalise();

                    sample = scene->raytrace(ray, 2);
                    total.add(sample);
                }
            }

            avg = total.divide(samplesize);
            
            // Ray ray;
            // double normalized_x = (((float)x)/XSIZE)-0.5;
            // double normalized_y = (((float)y)/YSIZE)-0.5;
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