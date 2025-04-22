#ifndef GFXBASE_H
#define GFXBASE_H

#include "math/vec3.h"
#include "math/Interval.h"

// Data structure for a single point of intersection with a surface
struct Collision {
    vec3<double> intersection;
    vec3<double> surface_normal;
    double t;
};

// Structure for a single intersection interval with an object
struct Span {
    Collision entry;
    Collision exit;
    Span* next; // linked list chaining multiple intersection intervals together
};

struct Ray {
    vec3<double> origin;
    vec3<double> direction;
};

using Collision = struct Collision;
using Ray = struct Ray;

#endif /* GFXBASE_H */