#ifndef BASEOBJECT_H
#define BASEOBJECT_H

#include <cstdint>
#include "GFXBase.h"

// Abstract shape class, shapes and surfaces must be able to be intersected by a ray
class BaseObject {
    public:
        virtual int32_t rayIntersect(Span* hit, Ray ray, Interval range)=0; // pure virtual
};

#endif /* BASEOBJECT_H */