#ifndef SPHERE_H
#define SPHERE_H

#include <cstdint>
#include <cmath>
#include "Geometry.h"
#include "GFXBase.h"
#include "vec3.h"
#include "Interval.h"

class Sphere : public Geometry {
    public:
        Sphere(vec3<double>& center, double radius);
        int32_t rayIntersect(Span* hit, Ray ray, Interval range);
        vec3<double> center;
        double radius;
};

#endif /* SPHERE_H */