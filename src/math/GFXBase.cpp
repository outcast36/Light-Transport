#include "GFXBase.h"

bool closerToOrigin(const Collision& p1, const Collision& p2) {
    return p1.t < p2.t;
}