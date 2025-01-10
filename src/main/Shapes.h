#ifndef SHAPES_H
#define SHAPES_H

#include <cstdint>
#include "Geometry.h"
#include "vec3.h"

// Abstract shape class, shapes must be able to be intersected by a ray
class Shape {
    public:
        virtual int32_t rayIntersect(Collision* hit, Ray ray)=0; // pure virtual function
};

class Sphere : public Shape {
    public:
        int32_t rayIntersect(Collision* hit, Ray ray);
        vec3<double> center;
        double radius;
};

class Plane : public Shape {
    public:
        int32_t rayIntersect(Collision* hit, Ray ray);
        vec3<double> point;
        vec3<double> normal;
};

class Cylinder : public Shape {
    public: 
        int32_t rayIntersect(Collision* hit, Ray ray);
        vec3<double> axis_of_rotation; // normal vector for some cross sectional plane of the cylinder
        double height;
        double radius;
}

#endif /* SHAPES_H */