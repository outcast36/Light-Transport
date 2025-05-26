#ifndef INTERVALSET_H
#define INTERVALSET_H

#include <memory>
#include <vector>
#include <array>
#include "Interval.h"
#include "Span.h"

// IntervalSet -- Structure for intersection intervals for a single ray intersection query 
// Invariant: For any intersection query that requires storage of three of more intersection intervals
// will create and use the vector disjointIntervals. The closest two intervals will always be stored in 
// the array, and every thing else will be stored in the vector. Both storage containers will be in 
// sorted order based on the lower bound values of their intervals.  
class IntervalSet {
 public:
  class Iterator {
   public: 
    // Iterator type definitions 
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = Span;
    using difference_type = std::ptrdiff_t;
    using pointer = Span*;
    using reference = Span&;
    
    explicit Iterator(IntervalSet* container, int32_t idx) 
        : set(container), idx(idx) {}
    reference operator*() { 
        if (idx < 2) {
            return set->inlineIntervals[idx];
        } 
        else return set->extraIntervals[idx-2];
    }
    pointer operator->() { return &(**this); }
    Iterator& operator++() {
        ++idx;
        return *this;
    }
    Iterator operator++(int) {
        Iterator res = *this;
        ++(*this);
        return res;
    }
    Iterator& operator--() {
        --idx;
        return *this;
    }
    Iterator operator--(int) {
        Iterator res = *this;
        --(*this);
        return res;
    }
    bool operator==(const Iterator& other) const {
        return set == other.set && idx == other.idx;
    }
    bool operator!=(const Iterator& other) const {
        return !(*this == other);
    }

   private: 
    IntervalSet* set;
    int32_t idx;
  };
  IntervalSet();
  IntervalSet(const Span& single);
  IntervalSet(const std::array<Span,2>& inlines);
  static IntervalSet empty(); 
  static IntervalSet fromSingleSpan(Span& primitive);
  std::string printIntervalSet();
  bool isEmpty() { return intervalCount == 0; }
  void push_back(Span& new_interval);
  void clear();
  void join(IntervalSet& other); // union operation
  void intersection(IntervalSet& other); // intersection operation
  void subtract(IntervalSet& other); // difference operation
  Iterator begin() { return Iterator(this,0); }
  Iterator end() { return Iterator(this, intervalCount); } // Don't dereference end()
  Iterator back() {
    if (!isEmpty()) return Iterator(this, intervalCount-1);
    else return end();
  }

 private: 
  std::array<Span, 2> inlineIntervals; // common case of one or two intervals
  std::vector<Span> extraIntervals; // overflow for more than two intervals
  size_t intervalCount; // if this is greater than one, the span contains disjoint intervals
};

#endif /* INTERVALSET_H */


// TODO add some sort of addInterval function so join() is easy