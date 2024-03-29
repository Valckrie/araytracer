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

const int samplesize = 16;

Colour frame_buffer[YSIZE][XSIZE];

float frand() {
    int x;
    float f;

    x = rand();
    f = (float)(x & 0xffff);
    f = f/65536.0;

    return f;
}

void write_framebuffer() {
    FILE *f;
    f = fopen("out.ppm","w");

    int x, y;
    float r, g, b;

    fprintf(f, "P3\n%d %d\n255\n", XSIZE, YSIZE);

    for(y=YSIZE-1;y>=0;y-=1) {
        for(x=0;x<XSIZE;x+=1) {
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

void clear_framebuffer() {
    int x,y;

    for(y=0;y<YSIZE;y+=1) {
        for(x=0;x<XSIZE;x+=1) {
          frame_buffer[y][x].clear();
        }
    }
}

// The main raytacing entry point.

int main(int argc, const char *argv[])
{
    Scene *scene;
    int x,y;

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

    // Create camera and set eye and look at positions
    Camera* cam = new Camera();
    cam->set_eye(-10, 5, -15, 1);
    cam->set_lookat(0, -3, 0, 1);
    cam->compute_uvw();

    // directional light 1
    Vector dir_light_dir(-1.0, -1.0, 0.0);
    DirectionalLight *dir_light1 = new DirectionalLight(dir_light_dir, col_white);
    dir_light1->turn_shadows(1);
    // scene->addLight(*dir_light1);

    // point light 1
    Vertex point_light_pos (8, 6, 0, 1.0);
    PointLight *pt_light1 = new PointLight(point_light_pos, col_white);
    pt_light1->setAttenuation(true);
    pt_light1->setLumScale(1.0);
    pt_light1->turn_shadows(1);
    scene->addLight(*pt_light1);

    // point light 2
    Vertex point_light_pos2 (-1, 8, -1, 1.0);
    PointLight *pt_light2 = new PointLight(point_light_pos2, col_white);
    pt_light2->setAttenuation(true);
    pt_light2->setLumScale(0.5);
    pt_light2->turn_shadows(1);
    scene->addLight(*pt_light2);
    
    // materials
    Material *grayMaterial = new Material();
    // specular red, green, blue materials
    Material *specR = new Material(0.9, 0.1, 0.1, 0.2, 0.8, 0.6);
    specR->set_exp(25);
    Material *specG = new Material(0.1, 0.9, 0.1, 0.2, 0.8, 0.6);
    specG->set_exp(25);
    Material *specB = new Material(0.3, 0.3, 0.7, 0.2, 0.8, 0.6);
    specB->set_exp(25);
    Material *specRR = new Material(0.9, 0.1, 0.1, 0.2, 0.8, 0.3);
    specRR->set_exp(1);

    // matte red, green, blue materials
    Material *matteR = new Material(0.8, 0.2, 0.2, 0.2, 0.8, 0.0);
    Material *matteG = new Material(0.2, 0.8, 0.2, 0.2, 0.8, 0.0);
    Material *matteB = new Material(0.2, 0.2, 0.8, 0.2, 0.8, 0.0);

    // reflective                      r     g     b     ka   kd   ks   kr
    Material *yellowR = new Material(0.75, 0.75, 0.0, 0.25, 0.5, 0.25, 1.0);
    yellowR->set_exp(101);

    Material *blackR = new Material(0.0, 0.0, 0.0, 0.35, 0.75, 0.0, 1.0);
    blackR->set_exp(1);

    // custom set materials inside material function
    Material *bronze = new Material(1);
    bronze->set_exp(25);
    Material *bronzeR = new Material(2);
    bronzeR->set_exp(25);
    Material *jadeR = new Material(3);
    Material *silverR = new Material(4);
    Material *glassI = new Material(5);
    Material *glassT = new Material(6);
    Material *emerald = new Material(7);
    emerald->set_type(3);
    Material *pearl = new Material(8);
    Material *turqoise = new Material(9);

    Material *glassTransparent = new Material(6);
    glassTransparent->set_ior(1.3);

    Material *checkerfloor = new Material(99);

    // create ground
    Plane *ground;
    Vertex ground_point(0, -5, 0, 1);
    Vector ground_normal(0, 1, 0);
    ground = new Plane(ground_point, ground_normal);
    ground->setMaterial(checkerfloor);
    scene->addObject(*ground);

    // triangle objects
    Triangle* triB = new Triangle();
    triB->setMaterial(matteB);

    Triangle* triG = new Triangle();
    triG->setMaterial(specG);

    Triangle* triY = new Triangle();
    triY->setMaterial(yellowR);

    Triangle* triR = new Triangle();
    triR->setMaterial(specR);

    Vertex origin (0, 0, 0, 1);
    float default_radius = 1;

    // create unit spheres with different materials

    Sphere* sphereGray = new Sphere(origin, default_radius);
    sphereGray->setMaterial(grayMaterial);

    Sphere* sphereMatteGreen = new Sphere(origin, default_radius);
    sphereMatteGreen->setMaterial(matteG);

    Sphere* sphereMatteRed = new Sphere(origin, default_radius);
    sphereMatteRed->setMaterial(matteR);

    Sphere* sphereMatteBlue = new Sphere(origin, default_radius);
    sphereMatteBlue->setMaterial(matteB);

    Sphere* sphereSpecRed = new Sphere(origin, default_radius);
    sphereSpecRed->setMaterial(specR);

    Sphere* sphereSpecGreen = new Sphere(origin, default_radius);
    sphereSpecGreen->setMaterial(specG);

    Sphere* sphereSpecBlue = new Sphere(origin, default_radius);
    sphereSpecBlue->setMaterial(specB);

    Sphere* sphereBronze = new Sphere(origin, default_radius);
    sphereBronze->setMaterial(bronzeR);

    Sphere* sphereSilver = new Sphere(origin, default_radius);
    sphereSilver->setMaterial(silverR);

    Sphere* sphereJade = new Sphere(origin, default_radius);
    sphereJade->setMaterial(jadeR);

    Sphere* sphereRefYellow = new Sphere(origin, default_radius);
    sphereRefYellow->setMaterial(yellowR);

    Sphere* sphereRefBlack = new Sphere(origin, default_radius);
    sphereRefBlack->setMaterial(blackR);

    Sphere* sphereGlassI = new Sphere(origin, default_radius);
    sphereGlassI->setMaterial(glassI);

    Sphere* sphereGlassT = new Sphere(origin, default_radius);
    sphereGlassT->setMaterial(glassT);

    Sphere* sphereGlass2 = new Sphere(origin, default_radius);
    sphereGlass2->setMaterial(glassTransparent);

    Sphere* sphereEmerald = new Sphere(origin, default_radius);
    sphereEmerald->setMaterial(emerald);

    Sphere* spherePearl = new Sphere(origin, default_radius);
    spherePearl->setMaterial(pearl);

    Sphere* sphereTurq = new Sphere(origin, default_radius);
    sphereTurq->setMaterial(turqoise);

    // disk and cylinder
    Disk* diskR = new Disk();
    diskR->setMaterial(bronze);

    Disk* diskG = new Disk();
    diskG->setMaterial(specG);

    OpenCylinder *ocR = new OpenCylinder(0, 1, 1);
    ocR->setMaterial(bronze);

    OpenCylinder *ocG = new OpenCylinder(0, 1, 1);
    ocG->setMaterial(specG);

    // Instance *oc1 = new Instance(ocR);
    // oc1->rotate_z(-60);
    // oc1->rotate_y(-60);
    // oc1->scale(1, 4, 1);
    // oc1->translate(0, -5, 0);
    // scene->addObject(*oc1);

    // Instance *disk1 = new Instance(diskR);
    // disk1->scale(2.0, 2.0, 2.0);
    // disk1->translate(0, -1, 0);
    // scene->addObject(*disk1);

    // Instance *tri1 = new Instance(triG);
    // tri1->scale(3.5, 3, 3.5);
    // tri1->rotate_x(15);
    // tri1->rotate_y(15);
    // tri1->rotate_z(15);
    // tri1->translate(0, 0, 0);
    // scene->addObject(*tri1);

    // Instance *tri2 = new Instance(triB);
    // tri2->scale(5, 8, 6);
    // tri2->rotate_x(30);
    // tri2->rotate_y(15);
    // tri2->rotate_z(5);
    // tri2->translate(0, -2, 0);
    // scene->addObject(*tri2);

    // Instance *tri3 = new Instance(triR);
    // tri3->scale(4, 6, 5);
    // tri3->rotate_x(-15);
    // tri3->rotate_y(-15);
    // tri3->rotate_z(-15);
    // tri3->translate(-3, -4, 0);
    // scene->addObject(*tri3);

    Instance *sph01 = new Instance(sphereBronze);
    sph01->scale(1.5, 1.5, 1.5);
    sph01->translate(0, -3.5, 0);
    scene->addObject(*sph01);

    Instance *sph02 = new Instance(sphereTurq);
    sph02->scale(2, 2, 2);
    sph02->translate(0, -3, 4.5);
    scene->addObject(*sph02);

    Instance *sph03 = new Instance(sphereMatteBlue);
    // sph03->scale(0.5, 0.5, 0.5);
    sph03->translate(0, -4, -3.5);
    scene->addObject(*sph03);

    Instance *sph04 = new Instance(spherePearl);
    sph04->scale(0.5, 0.5, 0.5);
    // sph04->rotate_x(60);
    // sph04->rotate_y(60);
    sph04->translate(-4.5, -2.5, -3.5);
    scene->addObject(*sph04);

    Instance *sph05 = new Instance(sphereEmerald);
    // sph05->scale(3, 2, 1);
    // sph05->translate(4, 2, 4);
    sph05->translate(-3, -4, -3.5);
    scene->addObject(*sph05);

    Instance *sph06 = new Instance(sphereJade);
    sph06->scale(0.5, 0.5, 0.5);
    // sph06->rotate_x(60);
    // sph06->rotate_z(60);
    sph06->translate(-6, -1.5, -3.5);
    scene->addObject(*sph06);

    Instance *sph07 = new Instance(sphereGlass2);
    // sphBrz->scale(2.5, 2.5, 2.5);
    sph07->translate(-6, 0, -3);
    scene->addObject(*sph07);

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

        // anti alias sampling

            for(int i = 0; i < ss; i++) {           // up sample
                for(int j = 0; j < ss; j++) {       // across sample

                    samplepixel.x = (double)x - 0.5 * XSIZE + (j + 0.5) / ss;
                    samplepixel.x = (double)(samplepixel.x / XSIZE);
                    samplepixel.y = (double)y - 0.5 * XSIZE + (i + 0.5) / ss;
                    samplepixel.y = (double)(samplepixel.y / XSIZE);
                    
                    // if( y == 0 && x == 0) 
                    //     cout << "AASSx " << samplepixel.x << " AASSy " << samplepixel.y << "\n";

                    Ray ray;
                    Vector ray_dir = cam->w.add(cam->u.multiply(samplepixel.x).add(cam->v.multiply(samplepixel.y)));
                    ray.P.set(cam->eye);
                    ray.D.set(ray_dir);
                    ray.D.normalise();

                    // trace ray with initial depth 0, primary ray
                    sample = scene->raytrace(ray, 0);

                    // add the sub sample colour to the pixel total
                    total.add(sample);
                }
            }

        // end aa

            // average the total sum of colours in the pixel by the sample size
            avg = total.returnDivide(samplesize);
            // Save result in frame buffer
            frame_buffer[y][x].red = avg.red;
            frame_buffer[y][x].green = avg.green;
            frame_buffer[y][x].blue = avg.blue;
        }
    }

    // OUTPUT IMAGE
    write_framebuffer();
}