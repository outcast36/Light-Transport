#ifndef BASEOBJECT_H
#define BASEOBJECT_H

#include <cstdint>
#include <optional>
#include "GFXBase.h"
#include "Interval.h"
#include "IntervalSet.h"

// Abstract class for primitives and CSG objects which require full intersection data
class BaseObject {
 public:
  virtual std::optional<IntervalSet> rayIntersect(Ray& ray, Interval range)=0; // pure virtual
  virtual ~BaseObject() = default;
};

#endif /* BASEOBJECT_H */