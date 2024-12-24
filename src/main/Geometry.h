#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "vec3.h"

struct Collision {
    vec3<double> intersection;
    vec3<double> surface_normal;
    double t;
};

struct Ray {
    vec3<double> origin;
    vec3<double> direction;
};

struct Plane {
    vec3<double> point;
    vec3<double> normal;
};

struct Sphere {
    vec3<double> center;
    double radius;
};

using Collision = struct Collision;
using Ray = struct Ray;
using Sphere = struct Sphere;

/* 
Overload the function rayIntersect depending on type of geometric primitive object.
Function overload is preferred over a template function in this case since the operations done
vary significantly between surface types 
*/
int32_t rayIntersect(Collision* hit, Ray ray, Sphere object);

#endif /* GEOMETRY_H */