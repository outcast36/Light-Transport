#ifndef RAYCASTTARGET_H
#define RAYCASTTARGET_H

#include <cstdint>
#include "object/GFXBase.h"
#include "math/Interval.h"

// Abstract class for primitives and CSG objects which require full intersection data
class RaycastTarget {
    public:
        virtual std::optional<Collision> rayIntersect(Ray& ray, Interval range)=0; // pure virtual
        virtual ~RaycastTarget() = default;
};

#endif /* RAYCASTTARGET_H */