#ifndef SPAN_H
#define SPAN_H

#include <algorithm>
#include <string> 
#include "GFXBase.h"
#include "Interval.h"

// Data structure for storing surface data about a single intersection interval
// Invariant: entry.t <= exit.t 
class Span {
 public:
  Span(const Collision& entry, const Collision& exit);
  static Span invalid(); 
  static Span initParametersOnly(double entry, double exit);
  std::string printSpan() const;
  Collision getEntry() const; 
  Collision getExit() const; 
  void setExit(const Collision& updated); 
  void setEntry(const Collision& updated);
  Interval asInterval();

 private: 
  Collision entry;
  Collision exit;
};

// Merge overlapping intervals into a single span 
Span mergeOverlap(const Span& a, const Span& b);

#endif /* SPAN_H */