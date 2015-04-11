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
    Vertex point_light_pos (0, 10, 0, 1.0);
    PointLight *pt_light1 = new PointLight(point_light_pos, col_white);
    pt_light1->setLumScale(2.0);
    pt_light1->turn_shadows(1);
    scene->addLight(*pt_light1);

    // POINT LIGHT SPHERE MARKER
    float marker_radius = 0.5;
    // addSphere(scene, point_light_pos, marker_radius, 1.0, 1.0, 1.0);
    
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

    Sphere* sphereGray = new Sphere(ellipse_c, ellipse_r);
    sphereGray->setMaterial(grayMaterial);

    Sphere* sphereGreen = new Sphere(ellipse_c, ellipse_r);
    sphereGreen->setMaterial(silverR);

    Sphere* sphereRed = new Sphere(ellipse_c, ellipse_r);
    sphereRed->setMaterial(specR);

    Sphere* sphereBlue = new Sphere(ellipse_c, ellipse_r);
    sphereBlue->setMaterial(specB);

    Sphere* sphBronze = new Sphere(ellipse_c, ellipse_r);
    sphBronze->setMaterial(bronzeR);

    Sphere* sphTransp = new Sphere(ellipse_c, ellipse_r);
    sphTransp->setMaterial(transp);

    Sphere* sphSilv = new Sphere(ellipse_c, ellipse_r);
    sphSilv->setMaterial(silverR);

    Instance *sphGra = new Instance(sphereGray);
    sphGra->scale(2.5, 2.5, 2.5);
    sphGra->rotate_y(0);
    sphGra->translate(0, 0, 0);
    scene->addObject(*sphGra);

    Instance *sphRed = new Instance(sphereRed);
    sphGra->scale(2.5, 2.5, 2.5);
    sphRed->rotate_y(0);
    sphRed->translate(6, 0, 0);
    scene->addObject(*sphRed);

    Instance *sphBrz = new Instance(sphereBronze);
    sphBrz->scale(2.5, 2.5, 2.5);
    sphBrz->rotate_y(0);
    sphBrz->translate(-6, 0, 0);
    scene->addObject(*sphBrz);