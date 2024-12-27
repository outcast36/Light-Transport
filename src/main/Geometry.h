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

using Collision = struct Collision;
using Ray = struct Ray;

#endif /* GEOMETRY_H */