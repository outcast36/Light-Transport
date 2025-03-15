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

// Union operation on two spheres
Scene scene4() {
    Scene scene_objects;
    vec3<double> rb_center(0,0.5,-5);
    Sphere rb(rb_center, 1);
    std::shared_ptr<Sphere> left_ptr = std::make_shared<Sphere>(rb);

    vec3<double> fb_center(0.75,0.5,-4.5);
    Sphere fb(fb_center, 1);
    std::shared_ptr<Sphere> right_ptr = std::make_shared<Sphere>(fb);

    CSG union_object(left_ptr, right_ptr, unions);
    std::shared_ptr<CSG> union_ptr = std::make_shared<CSG>(union_object);

    scene_objects.add(union_ptr);
    return scene_objects;
}

// A sphere with a cylinder parallel to the z-axis cut out from the center
Scene scene5() {
    Scene scene_objects;
    vec3<double> rb_center(0,0.5,-5);
    Sphere rb(rb_center, 1);
    std::shared_ptr<Sphere> left_ptr = std::make_shared<Sphere>(rb);

    vec3<double> cylinder_axis(0,0,1);
    vec3<double> cylinder_base_point(0,0.5,-6);
    Cylinder vert(cylinder_axis, cylinder_base_point, 3, 0.5);
    std::shared_ptr<Cylinder> right_ptr = std::make_shared<Cylinder>(vert);

    CSG difference_object(left_ptr, right_ptr, difference);
    std::shared_ptr<CSG> cut_ptr = std::make_shared<CSG>(difference_object);

    scene_objects.add(cut_ptr);
    return scene_objects;
}

// Unit height and radius cylinder angled up off the xz-plane
Scene scene6() {
    Scene scene_objects;
    vec3<double> cylinder_axis(0,1,0);
    cylinder_axis = unitVector(cylinder_axis);
    vec3<double> cylinder_base_point(0,-2,-5);

    Cylinder angled(cylinder_axis, cylinder_base_point, 1, 1);
    std::shared_ptr<Cylinder> cyl_ptr = std::make_shared<Cylinder>(angled);

    scene_objects.add(cyl_ptr);
    return scene_objects;
}

// Discs that should be appearing in scene6 renders
Scene scene7() {
    Scene scene_objects;
    vec3<double> bot_center(0,-2,-5);
    vec3<double> bot_norm(0,-1,0);
    vec3<double> top_norm(0,1,0);
    vec3<double> top_center(0,-1,-5);

    Disc bot(bot_center, bot_norm, 1);
    std::shared_ptr<Disc> bot_ptr = std::make_shared<Disc>(bot);

    Disc top(top_center, top_norm, 1);
    std::shared_ptr<Disc> top_ptr = std::make_shared<Disc>(top);

    scene_objects.add(bot_ptr);
    scene_objects.add(top_ptr);
    return scene_objects;
}