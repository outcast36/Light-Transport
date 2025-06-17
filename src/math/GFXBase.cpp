#include "GFXBase.h"

Collision Collision::parameterOnly(double t) {
    Collision ret;
    ret.t = t;
    return ret;
}

bool closerToOrigin(const Collision& p1, const Collision& p2) {
    return p1.t < p2.t;
}

bool closerOrTouching(const Collision& p1, const Collision& p2) {
    // This will likely need to change to use epsilon in the future to correctly
    // handle cases where p1.t == p2.t
    return p1.t <= p2.t;
}