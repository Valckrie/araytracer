    Colour col_white;
    col_white.set(1.0,1.0,1.0,1.0);

    Camera* cam = new Camera();
    cam->set_eye(0, 10, 25, 1);
    cam->set_lookat(0, 5, 0, 1);
    cam->compute_uvw();

    // Create and add a directional light to the scene
    Vector dir_light_dir(-1.0, -1.0, 0.0);
    DirectionalLight *dir_light1 = new DirectionalLight(dir_light_dir, col_white);
    dir_light1->turn_shadows(1);
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
    // addSphere(scene, testpos, test, 0.8, 0.1, 0.3);

    Vertex testpos2 (2, 2, 0, 1.0);
    float test2 = 1;
    // addSphere(scene, testpos2, test2, 0.5, 0.5, 0.5);


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
    Material *grayR = new Material(3);
    Material *silverR = new Material(4);
    Material *transp = new Material(5);

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
    sphereGreen->setMaterial(silverR);

    Sphere* sphereSpec = new Sphere(ellipse_c, ellipse_r);
    sphereSpec->setMaterial(silverR);

    Sphere* sphereRed = new Sphere(ellipse_c, ellipse_r);
    sphereRed->setMaterial(specR);

    Sphere* sphereBlue = new Sphere(ellipse_c, ellipse_r);
    sphereBlue->setMaterial(specB);

    Sphere* sphBrz = new Sphere(ellipse_c, ellipse_r);
    sphBrz->setMaterial(bronzeR);

    Sphere* sphTransp = new Sphere(ellipse_c, ellipse_r);
    sphTransp->setMaterial(transp);

    Sphere* sphG = new Sphere(ellipse_c, ellipse_r);
    sphG->setMaterial(grayR);

    Sphere* sphSilv = new Sphere(ellipse_c, ellipse_r);
    sphSilv->setMaterial(silverR);

    Instance *e1 = new Instance(sphBrz);
    e1->scale(2.5, 2.5, 2.5);
    e1->rotate_y(0);
    e1->translate(0, 0, 0);
    scene->addObject(*e1);

    Instance *e11 = new Instance(sphTransp);
    e11->scale(3, 3, 3);
    e11->rotate_y(0);
    e11->translate(0, 6, 0);
    scene->addObject(*e11);

    Instance *sphgray = new Instance(sphG);
    sphgray->scale(2.5, 2.5, 2.5);
    sphgray->rotate_y(0);
    sphgray->translate(7, -3.5, 0);
    scene->addObject(*sphgray);

    Instance *e2 = new Instance(sphG);
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

    Instance *e5 = new Instance(sphBrz);
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
    // scene->addObject(*e7);

    // Triangle *triangle1 = new Triangle(Vertex(-5, 10, 1), Vertex(0, 15, 1), Vertex(5, 10, 1));
    // triangle1->setMaterial(newMaterial);

    // Instance *tri1 = new Instance(triangle1);
    // tri1->rotate_z(0);
    // tri1->translate(0, 0, 0);
    // scene->addObject(*tri1);

    OpenCylinder *opencylinder1 = new OpenCylinder(0, 1, 2.2);
    opencylinder1->setMaterial(silverR);

    Instance *oc1 = new Instance(opencylinder1);
    // oc1->rotate_z(-60);
    // oc1->rotate_y(-60);
    oc1->scale(1, 8.5, 1);
    oc1->translate(-5, -5, -5);
    scene->addObject(*oc1);