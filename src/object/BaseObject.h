#ifndef BASEOBJECT_H
#define BASEOBJECT_H

#include <cstdint>
#include <optional>
#include <vector>
#include "GFXBase.h"
#include "Span.h"
#include "Interval.h"

// Abstract class for primitives and CSG objects which require full intersection data
class BaseObject {
 public:
  virtual std::optional<std::vector<Span>> rayIntersect(Ray& ray)=0; // pure virtual
  virtual ~BaseObject() = default;
};

#endif /* BASEOBJECT_H */