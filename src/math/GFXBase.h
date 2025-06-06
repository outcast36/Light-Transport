#ifndef GFXBASE_H
#define GFXBASE_H

#include "vec3.h"

// Data structure for a single point of intersection with a surface
struct Collision {
    vec3<double> intersection;
    vec3<double> surface_normal;
    double t;
};

struct Ray {
    vec3<double> origin;
    vec3<double> direction;
};

using Ray = struct Ray;
using Collision = struct Collision;

// Less than operation between two collisions for a single ray-intersection 
// query (i.e. the two collisions are along the same ray) return true if the
// collision p1 has a ray parameter (t) less than that of p2 and false otherwise. 
bool closerToOrigin(const Collision& p1, const Collision& p2);

// Less than or equal to operation between two collisions within a single
// ray intersection query. Used to generate correct interval lists when
// combining with boolean operations for use with CSG. 
bool closerOrTouching(const Collision& p1, const Collision& p2);

#endif /* GFXBASE_H */