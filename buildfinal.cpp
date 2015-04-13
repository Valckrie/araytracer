Colour col_white;
    col_white.set(1.0,1.0,1.0,1.0);

    Camera* cam = new Camera();
    cam->set_eye(8, 8, 8, 1);
    // cam->set_eye(10, 5, -15, 1);
    // cam->set_eye(6, 2, -9, 1);
    cam->set_lookat(0, -3, 0, 1);
    // cam->set_eye(2, 1, 3, 1);
    // cam->set_lookat(-3, -3, 2, 1);
    // 8 , 2.5, 12
    cam->compute_uvw();

    // Create and add a directional light to the scene
    Vector dir_light_dir(-1.0, -1.0, 0.0);
    DirectionalLight *dir_light1 = new DirectionalLight(dir_light_dir, col_white);
    dir_light1->turn_shadows(1);
    // scene->addLight(*dir_light1);

    // POINT LIGHT
    Vertex point_light_pos (0, 10, 0, 1.0);
    PointLight *pt_light1 = new PointLight(point_light_pos, col_white);
    pt_light1->setLumScale(1.0);
    pt_light1->turn_shadows(1);
    // scene->addLight(*pt_light1);

    Vertex point_light_pos2 (0, 7.5, 7.5, 1.0);
    PointLight *pt_light2 = new PointLight(point_light_pos2, col_white);
    pt_light2->setAttenuation(true);
    pt_light2->setLumScale(1.0);
    pt_light2->turn_shadows(1);
    scene->addLight(*pt_light2);

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
    // specR->copySpecular();
    // specG->copySpecular();
    // specB->copySpecular();
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

    Vertex ellipse_c (0, 0, 0, 1);
    float ellipse_r = 1;

    Disk* disk = new Disk();
    disk->setMaterial(matteG);

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

    Instance *sph01 = new Instance(sphereSpecRed);
    // sphBrz->scale(2.5, 2.5, 2.5);
    sph01->translate(3, -4, 3);
    scene->addObject(*sph01);

    Instance *sph02 = new Instance(sphereSpecGreen);
    // sphBrz->scale(2.5, 2.5, 2.5);
    sph02->translate(0, -4, 3);
    scene->addObject(*sph02);

    Instance *sph03 = new Instance(sphereSpecBlue);
    // sphBrz->scale(2.5, 2.5, 2.5);
    sph03->translate(-3, -4, 3);
    scene->addObject(*sph03);

    Instance *sph04 = new Instance(sphereBronze);
    // sphGra->scale(2.5, 2.5, 2.5);
    sph04->translate(3, -4, 0);
    scene->addObject(*sph04);

    Instance *sph05 = new Instance(sphereJade);
    // sphBrz->scale(2.5, 2.5, 2.5);
    sph05->translate(0, -4, 0);
    scene->addObject(*sph05);

    Instance *sph06 = new Instance(sphereSilver);
    // sphRed->scale(2.5, 2.5, 2.5);
    sph06->translate(-3, -4, 0);
    scene->addObject(*sph06);

    Instance *sph07 = new Instance(sphereMatteRed);
    // sphBrz->scale(2.5, 2.5, 2.5);
    sph07->translate(3, -4, -3);
    scene->addObject(*sph07);

    Instance *sph08 = new Instance(sphereMatteGreen);
    // sphBrz->scale(2.5, 2.5, 2.5);
    sph08->translate(0, -4, -3);
    scene->addObject(*sph08);

    Instance *sph09 = new Instance(sphereMatteBlue);
    // sphBrz->scale(2.5, 2.5, 2.5);
    sph09->translate(-3, -4, -3);
    scene->addObject(*sph09);

    Instance *sph10 = new Instance(sphereRefYellow);
    // sphBrz->scale(2.5, 2.5, 2.5);
    sph10->translate(3, -1, 0);
    scene->addObject(*sph10);

    Instance *sph11 = new Instance(sphereGlassI);
    // sphBrz->scale(2.5, 2.5, 2.5);
    sph11->translate(3, -1, 3);
    scene->addObject(*sph11);

    Instance *sph12 = new Instance(sphereGlassT);
    // sphBrz->scale(2.5, 2.5, 2.5);
    sph12->translate(3, -1, -3);
    scene->addObject(*sph12);

    Instance *disk1 = new Instance(disk);
    // disk1->scale(2.5, 2.5, 2.5);
    disk1->translate(0, -2, 0);
    // scene->addObject(*disk1);