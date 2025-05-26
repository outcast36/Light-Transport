#ifndef SPAN_H
#define SPAN_H

#include <algorithm>
#include <string> 
#include "GFXBase.h"

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
  std::string printSpan() const;
  Collision getEntry() const; 
  Collision getExit() const; 
  void setExit(const Collision& updated); 
  void setEntry(const Collision& updated); 
  // Merge overlapping intervals into a single span by updating the exit object
  // to the one that has the larger ray parameter (t)
  void mergeOverlap(const Span& other);

 private: 
  Collision entry;
  Collision exit;
};

#endif /* SPAN_H */