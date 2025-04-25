#ifndef BASEOBJECT_H
#define BASEOBJECT_H

#include <cstdint>
#include "object/GFXBase.h"
#include "object/Span.h"

// Abstract class for primitives and CSG objects which require full intersection data
class BaseObject {
    public:
        virtual int32_t rayIntersect(Span* hit, Ray ray, Interval range)=0; // pure virtual
        virtual ~BaseObject() = default;
};

#endif /* BASEOBJECT_H */