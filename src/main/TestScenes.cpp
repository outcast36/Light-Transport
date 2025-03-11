#include "TestScenes.h"

Scene scene1() {
    Scene scene_objects;
    vec3<double> rb_center(0,0.5,-2.5);
    Sphere rb(rb_center, 0.5);
    std::shared_ptr<Sphere> sphere_ptr = std::make_shared<Sphere>(rb);

    vec3<double> fb_center(0,-100.5,-1);
    Sphere fb(fb_center, 100);
    std::shared_ptr<Sphere> floor_ptr = std::make_shared<Sphere>(fb);

    scene_objects.add(sphere_ptr);
    scene_objects.add(floor_ptr);
    return scene_objects;
}

// A single unit height and unit radius cylinder aligned with the y-axis
Scene scene2() {
    Scene scene_objects;
    vec3<double> cylinder_axis(0,1,0);
    vec3<double> cylinder_base_point(0,0,-5);
    Cylinder vert(cylinder_axis, cylinder_base_point, 1, 1);
    std::shared_ptr<Cylinder> cylinder_ptr = std::make_shared<Cylinder>(vert);

    scene_objects.add(cylinder_ptr);
    return scene_objects;
}

// A single unit height cone with theta == pi/6 (30 degrees), aligned with the y-axis
Scene scene3() {
    Scene scene_objects;
    vec3<double> cone_axis(0,-1,0);
    vec3<double> cone_apex(0,1,-5);
    double theta = M_PI/6;  // cos(pi / 6) = sqrt(3)/2, sin(pi / 6) = 1/2
    Cone vert(cone_axis, cone_apex, 1, theta);
    std::shared_ptr<Cone> cone_ptr = std::make_shared<Cone>(vert);

    scene_objects.add(cone_ptr);
    return scene_objects;
}