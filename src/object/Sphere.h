#ifndef SPHERE_H
#define SPHERE_H

#include <cmath>
#include "BaseObject.h"

class Sphere : public BaseObject {
    public:
        Sphere(vec3<double>& center, double radius);
        int32_t rayIntersect(Span* hit, Ray ray, Interval range);
        vec3<double> center;
        double radius;
};

#endif /* SPHERE_H */