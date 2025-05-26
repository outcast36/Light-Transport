#ifndef GFXBASE_H
#define GFXBASE_H

#include "vec3.h"

// Data structure for a single point of intersection with a surface
struct Collision {
    vec3<double> intersection;
    vec3<double> surface_normal;
    double t;
    bool operator<(const Collision& other) const { return t < other.t; }
};

struct Ray {
    vec3<double> origin;
    vec3<double> direction;
};

using Collision = struct Collision;
using Ray = struct Ray;

#endif /* GFXBASE_H */