#include <cmath>
#include "GFXBase.h"

Collision Collision::parameterOnly(double t) {
    Collision ret;
    ret.t = t;
    return ret;
}

bool withinEpsilon(double t1, double t2, double epsilon) {
    return std::abs(t2 - t1) < epsilon;
}

bool closerToOrigin(const Collision& p1, const Collision& p2) {
    return p1.t < p2.t;
}

bool closerOrTouching(const Collision& p1, const Collision& p2) {
    return p1.t < p2.t || withinEpsilon(p1.t, p2.t);
}