#ifndef SPAN_H
#define SPAN_H

#include "object/GFXBase.h"

// Data structure for storing surface data about a single intersection interval
// Invariant: entry.t <= exit.t 
class Span {
 public:
  Span(const Collision& entry, const Collision& exit) 
      : entry(entry), exit(exit) {}
  static Span invalid() {
      Collision dummy{vec3<double>(), vec3<double>(), 0.0};
      return Span(dummy, dummy);
  }
 private: 
  Collision entry;
  Collision exit;
};

#endif /* SPAN_H */