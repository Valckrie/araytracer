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
#include "include/disk.h"

using namespace std;

#define XSIZE 640
#define YSIZE 480

const int samplesize = 9;

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


    int ss = (int)sqrt( (float)samplesize);
    Vertex samplepixel;

    // srand(30115);
    srand(time(NULL));

    clear_framebuffer();

    // Create a new scene to render
    scene = new Scene();

// SETUP SCENE

    Colour col_white;
    col_white.set(1.0,1.0,1.0,1.0);

    Camera* cam = new Camera();
    // cam->set_eye(-4, 2, 6, 1);
    cam->set_eye(-10, 5, -15, 1);
    // cam->set_eye(6, 2, -9, 1);
    cam->set_lookat(0, -3, 0, 1);
    // cam->set_eye(2, 1, 3, 1);
    // cam->set_lookat(-3, -3, 2, 1);
    // 8 , 2.5, 12
    cam->compute_uvw();

    // Create and add a directional light to the scene
    Vector dir_light_dir(1.0, 1.0, 0.0);
    DirectionalLight *dir_light1 = new DirectionalLight(dir_light_dir, col_white);
    dir_light1->turn_shadows(1);
    scene->addLight(*dir_light1);

    // POINT LIGHT
    Vertex point_light_pos (12, 6, -10, 1.0);
    PointLight *pt_light1 = new PointLight(point_light_pos, col_white);
    pt_light1->setAttenuation(true);
    pt_light1->setLumScale(1.0);
    pt_light1->turn_shadows(1);
    // scene->addLight(*pt_light1);

    Vertex point_light_pos2 (8, 6, -10, 1.0);
    PointLight *pt_light2 = new PointLight(point_light_pos2, col_white);
    pt_light2->setAttenuation(true);
    pt_light2->setLumScale(1.0);
    pt_light2->turn_shadows(1);
    // scene->addLight(*pt_light2);

    // POINT LIGHT SPHERE MARKER
    float marker_radius = 0.5;
    // addSphere(scene, point_light_pos, marker_radius, 1.0, 1.0, 1.0);
    
    Material *grayMaterial = new Material();
    Material *specR = new Material(0.9, 0.1, 0.1, 0.2, 0.8, 0.6);
    specR->set_exp(25);
    Material *specG = new Material(0.1, 0.9, 0.1, 0.2, 0.8, 0.6);
    specG->set_exp(25);
    Material *specB = new Material(0.3, 0.3, 0.7, 0.2, 0.8, 0.6);
    specB->set_exp(25);
    Material *specRR = new Material(0.9, 0.1, 0.1, 0.2, 0.8, 0.3);
    specRR->set_exp(1);

    Material *matteR = new Material(0.8, 0.2, 0.2, 0.2, 0.8, 0.0);
    Material *matteG = new Material(0.2, 0.8, 0.2, 0.2, 0.8, 0.0);
    Material *matteB = new Material(0.2, 0.2, 0.8, 0.2, 0.8, 0.0);

    //                                r     g     b     ka   kd   ks   kr
    Material *yellowR = new Material(0.75, 0.75, 0.0, 0.25, 0.5, 0.25, 1.0);
    yellowR->set_exp(101);

    Material *blackR = new Material(0.0, 0.0, 0.0, 0.35, 0.75, 0.0, 1.0);
    blackR->set_exp(1);

    Material *bronze = new Material(1);
    bronze->set_exp(25);
    Material *bronzeR = new Material(2);
    bronzeR->set_exp(25);
    Material *jadeR = new Material(3);
    Material *silverR = new Material(4);
    Material *glassI = new Material(5);
    Material *glassT = new Material(6);

    Material *checkerfloor = new Material(99);

    Plane *ground;
    Vertex ground_point(0, -5, 0, 1);
    Vector ground_normal(0, 1, 0);
    ground = new Plane(ground_point, ground_normal);
    ground->setMaterial(checkerfloor);
    scene->addObject(*ground);

    Triangle* triB = new Triangle();
    triB->setMaterial(matteB);

    Triangle* triG = new Triangle();
    triG->setMaterial(specG);

    Triangle* triY = new Triangle();
    triY->setMaterial(yellowR);

    Triangle* triR = new Triangle();
    triR->setMaterial(specR);

    Vertex ellipse_c (0, 0, 0, 1);
    float ellipse_r = 1;


    Sphere* sphereGray = new Sphere(ellipse_c, ellipse_r);
    sphereGray->setMaterial(grayMaterial);

    Sphere* sphereMatteGreen = new Sphere(ellipse_c, ellipse_r);
    sphereMatteGreen->setMaterial(matteG);

    Sphere* sphereMatteRed = new Sphere(ellipse_c, ellipse_r);
    sphereMatteRed->setMaterial(matteR);

    Sphere* sphereMatteBlue = new Sphere(ellipse_c, ellipse_r);
    sphereMatteBlue->setMaterial(matteB);

    Sphere* sphereSpecRed = new Sphere(ellipse_c, ellipse_r);
    sphereSpecRed->setMaterial(specR);

    Sphere* sphereSpecGreen = new Sphere(ellipse_c, ellipse_r);
    sphereSpecGreen->setMaterial(specG);

    Sphere* sphereSpecBlue = new Sphere(ellipse_c, ellipse_r);
    sphereSpecBlue->setMaterial(specB);

    Sphere* sphereBronze = new Sphere(ellipse_c, ellipse_r);
    sphereBronze->setMaterial(bronzeR);

    Sphere* sphereSilver = new Sphere(ellipse_c, ellipse_r);
    sphereSilver->setMaterial(silverR);

    Sphere* sphereJade = new Sphere(ellipse_c, ellipse_r);
    sphereJade->setMaterial(jadeR);

    Sphere* sphereRefYellow = new Sphere(ellipse_c, ellipse_r);
    sphereRefYellow->setMaterial(yellowR);

    Sphere* sphereRefBlack = new Sphere(ellipse_c, ellipse_r);
    sphereRefBlack->setMaterial(blackR);

    Sphere* sphereGlassI = new Sphere(ellipse_c, ellipse_r);
    sphereGlassI->setMaterial(glassI);

    Sphere* sphereGlassT = new Sphere(ellipse_c, ellipse_r);
    sphereGlassT->setMaterial(glassT);


    Disk* diskR = new Disk();
    diskR->setMaterial(bronze);

    Disk* diskG = new Disk();
    diskG->setMaterial(specG);

    OpenCylinder *ocR = new OpenCylinder(0, 1, 1);
    ocR->setMaterial(bronze);

    OpenCylinder *ocG = new OpenCylinder(0, 1, 1);
    ocG->setMaterial(specG);

    Instance *oc1 = new Instance(ocR);
    // oc1->rotate_z(-60);
    // oc1->rotate_y(-60);
    oc1->scale(1, 4, 1);
    oc1->translate(0, -5, 0);
    scene->addObject(*oc1);

    Instance *oc2 = new Instance(ocG);
    // oc1->rotate_z(-60);
    // oc1->rotate_y(-60);
    oc2->scale(1, 4, 1);
    oc2->rotate_x(90);
    oc2->translate(-4, -4, -2);
    // scene->addObject(*oc2);

    Instance *disk1 = new Instance(diskR);
    // disk1->scale(2.0, 2.0, 2.0);
    disk1->translate(0, -1, 0);
    scene->addObject(*disk1);

    Instance *disk2 = new Instance(diskG);
    disk2->rotate_x(90);
    // disk1->scale(2.0, 2.0, 2.0);
    disk2->translate(-4, -4, 2);
    // scene->addObject(*disk2);

    Instance *sph01 = new Instance(sphereBronze);
    // sphBrz->scale(2.5, 2.5, 2.5);
    sph01->translate(0, -4, 0);
    // scene->addObject(*sph01);

    Instance *sph02 = new Instance(sphereSpecRed);
    // sphBrz->scale(2.5, 2.5, 2.5);
    sph02->translate(0, -4, 3);
    scene->addObject(*sph02);

    Instance *sph03 = new Instance(sphereJade);
    // sph03->scale(0.5, 0.5, 0.5);
    sph03->translate(0, -4, -3);
    scene->addObject(*sph03);



    Instance *tri1 = new Instance(triG);
    tri1->scale(3.5, 3, 3.5);
    tri1->rotate_x(15);
    tri1->rotate_y(15);
    tri1->rotate_z(15);
    tri1->translate(0, 0, 0);
    // scene->addObject(*tri1);

    Instance *tri2 = new Instance(triB);
    tri2->scale(5, 8, 6);
    tri2->rotate_x(30);
    tri2->rotate_y(15);
    tri2->rotate_z(5);
    tri2->translate(0, -2, 0);
    // scene->addObject(*tri2);

    Instance *tri3 = new Instance(triR);
    tri3->scale(4, 6, 5);
    tri3->rotate_x(-15);
    tri3->rotate_y(-15);
    tri3->rotate_z(-15);
    tri3->translate(-3, -4, 0);
    // scene->addObject(*tri3);

    Instance *sph04 = new Instance(sphereSpecRed);
    sph04->scale(1.0, 1.0, 2.0);
    sph04->rotate_x(60);
    sph04->rotate_y(60);
    sph04->translate(4, -4, 0);
    // scene->addObject(*sph04);

    Instance *sph05 = new Instance(sphereSpecBlue);
    // sph05->scale(3, 2, 1);
    // sph05->translate(4, 2, 4);
    sph05->translate(0, -4, 0);
    // sph05->rotate_x(40);
    // scene->addObject(*sph05);

    Instance *sph06 = new Instance(sphereSpecGreen);
    sph06->scale(1.0, 2.0, 1.0);
    sph06->rotate_x(60);
    sph06->rotate_z(60);
    sph06->translate(-4, -4, 0);
    // scene->addObject(*sph06);

    Instance *sph07 = new Instance(sphereMatteRed);
    // sphBrz->scale(2.5, 2.5, 2.5);
    sph07->translate(3, -4, -3);
    // scene->addObject(*sph07);

    Instance *sph08 = new Instance(sphereMatteGreen);
    // sphBrz->scale(2.5, 2.5, 2.5);
    sph08->translate(0, -4, -3);
    // scene->addObject(*sph08);

    Instance *sph09 = new Instance(sphereMatteBlue);
    // sphBrz->scale(2.5, 2.5, 2.5);
    sph09->translate(-3, -4, -3);
    // scene->addObject(*sph09);

    Instance *sph10 = new Instance(sphereRefYellow);
    // sphBrz->scale(2.5, 2.5, 2.5);
    sph10->translate(3, -1, 0);
    // scene->addObject(*sph10);

    Instance *sph11 = new Instance(sphereGlassI);
    // sphBrz->scale(2.5, 2.5, 2.5);
    sph11->translate(3, -1, 3);
    // scene->addObject(*sph11);

    Instance *sph12 = new Instance(sphereGlassT);
    // sphBrz->scale(2.5, 2.5, 2.5);
    sph12->translate(3, -1, -3);
    // scene->addObject(*sph12);



// end setup scene

    // RAYTRACE SCENE

    cout << "Sample size " << samplesize << "\n";
    cout << "Sqrt Ss " << ss << "\n";

    for(y = 0; y < YSIZE; y++) {                    // up main
        for(x = 0; x < XSIZE; x++) {                // across main

            Colour total;
            Colour avg;
            Colour sample;

            // double samplex = (((float)x)/XSIZE) - 0.5;
            // double sampley = (((float)y)/XSIZE) - 0.5;
            // cout << "ORIGX " << samplex << " ORIGY " << sampley << "\n";

            // for(int i = 0; i < ss; i++) {           // up sample
            //     for(int j = 0; j < ss; j++) {       // across sample

            //     // pp.x = vp.s * (c - 0.5 * vp.hres + (q + 0.5) / n); 
            //     // pp.y = vp.s * (r - 0.5 * vp.vres + (p + 0.5) / n);

            //         samplepixel.x = (double)x - 0.5 * XSIZE + (j + 0.5) / ss;
            //         samplepixel.x = (double)(samplepixel.x / XSIZE);
            //         samplepixel.y = (double)y - 0.5 * XSIZE + (i + 0.5) / ss;
            //         samplepixel.y = (double)(samplepixel.y / XSIZE);
                    
            //         // samplepixel.x = ((float)x/XSIZE) - 0.5 * XSIZE + (j + 0.5) / ss;
            //         // samplepixel.y = ((float)y/YSIZE) - 0.5 * YSIZE + (i + 0.5) / ss;

            //         // cout << "AASSx " << samplepixel.x << " AASSy " << samplepixel.y << "\n";
            //         Ray ray;
            //         ray.P.set(samplepixel.x, samplepixel.y, 25.0, 1.0);
            //         Vector ray_dir (0, 0, -1);
            //         ray.D.set(ray_dir);
            //         // ray.D.normalise();

            //         sample = scene->raytrace(ray, 0);
            //         total.add(sample);
            //     }
            // }


        // anti alias sampling

            for(int i = 0; i < ss; i++) {           // up sample
                for(int j = 0; j < ss; j++) {       // across sample

                // pp.x = vp.s * (c - 0.5 * vp.hres + (q + 0.5) / n); 
                // pp.y = vp.s * (r - 0.5 * vp.vres + (p + 0.5) / n);

                    samplepixel.x = (double)x - 0.5 * XSIZE + (j + 0.5) / ss;
                    samplepixel.x = (double)(samplepixel.x / XSIZE);
                    samplepixel.y = (double)y - 0.5 * XSIZE + (i + 0.5) / ss;
                    samplepixel.y = (double)(samplepixel.y / XSIZE);
                    
                    // samplepixel.x = ((float)x/XSIZE) - 0.5 * XSIZE + (j + 0.5) / ss;
                    // samplepixel.y = ((float)y/YSIZE) - 0.5 * YSIZE + (i + 0.5) / ss;

                    // if( y == 0 && x == 0) 
                    //     cout << "AASSx " << samplepixel.x << " AASSy " << samplepixel.y << "\n";

                    Ray ray;
                    ray.P.set(cam->eye);
                    Vector ray_dir = cam->w.add(cam->u.multiply(samplepixel.x).add(cam->v.multiply(samplepixel.y)));
                    ray.D.set(ray_dir);
                    ray.D.normalise();

                    sample = scene->raytrace(ray, 0);
                    total.add(sample);
                }
            }

        // end aa

            avg = total.returnDivide(samplesize);
            // 
            
            // Ray ray;
            // double normalized_x = (((float)x)/XSIZE)-0.5;
            // double normalized_y = (((float)y)/XSIZE)-0.5;

            // if( y == 0 && x == 0) 
            //             cout << "AASSx " << normalized_x << " AASSy " << normalized_y << "\n";

            // Vector ray_dir = cam->w.add(cam->u.multiply(normalized_x).add(cam->v.multiply(normalized_y)));
            // ray.P.set(cam->eye);
            // ray.D.set(ray_dir);
            // ray.D.normalise();
            // avg = scene->raytrace(ray, 0);

            // avg.add(avg);
            // avg = avg.returnDivide(2);

            // Save result in frame buffer
            frame_buffer[y][x].red = avg.red;
            frame_buffer[y][x].green = avg.green;
            frame_buffer[y][x].blue = avg.blue;
        }
    }

    // OUTPUT IMAGE

    write_framebuffer();
}