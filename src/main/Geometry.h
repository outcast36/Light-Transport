#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <cstdint>
#include <memory>
#include <vector>
#include "GFXBase.h"
#include "vec3.h"
#include "Interval.h"

// Abstract shape class, shapes and surfaces must be able to be intersected by a ray
class Geometry {
    public:
        virtual int32_t rayIntersect(Collision* hit, Ray ray, Interval& range)=0; // pure virtual function
};

// Class for list of geometric objects, wrap the closest intersection method as a 
// rayIntersect implementation 
class Scene : public Geometry {
    public:
        Scene();
        int32_t rayIntersect(Collision* hit, Ray ray, Interval& range);
        void add(std::shared_ptr<Geometry>); // push_back wrapper
        void clearScene();
        std::vector<std::shared_ptr<Geometry>> geometry_list; // list of objects in the scene
};

class Sphere : public Geometry {
    public:
        Sphere(vec3<double>& center, double radius);
        int32_t rayIntersect(Collision* hit, Ray ray, Interval& range);
        vec3<double> center;
        double radius;
};

class Plane : public Geometry {
    public:
        Plane(vec3<double>& point, vec3<double>& normal);
        int32_t rayIntersect(Collision* hit, Ray ray, Interval& range);
        vec3<double> point;
        vec3<double> normal;
};

class Cylinder : public Geometry {
    public: 
        Cylinder(vec3<double>& axis, vec3<double>& point, double height, double radius);
        int32_t rayIntersect(Collision* hit, Ray ray, Interval& range);
        vec3<double> axis_of_rotation; // normal vector for some cross sectional plane of the cylinder
        vec3<double> point_in_center; // point on line forming axis of rotation
        double height;
        double radius;
};

class Cone : public Geometry {
    public: 
        Cone(vec3<double>& axis, vec3<double>& point, double height, double theta);
        int32_t rayIntersect(Collision* hit, Ray ray, Interval& range);
        vec3<double> axis_of_rotation;
        vec3<double> apex;
        double height;
        double theta;
};

// for sure torus, ellipsoid, triangle, 
// maybe pyramid, cube, polygon, polyhedra, general rotation surface -- general 2D curve not just lines

#endif /* GEOMETRY_H */