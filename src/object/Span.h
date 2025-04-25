#ifndef SPAN_H
#define SPAN_H

#include <memory>
#include <vector>
#include <array>
#include "math/Interval.h"
#include "object/GFXBase.h"

// Span -- Structure for intersection intervals for a single ray intersection query 
// Invariant: For any intersection query that requires storage of three of more intersection intervals
// will create and use the vector disjointIntervals. The closest two intervals will always be stored in 
// the array, and every thing else will be stored in the vector. Both storage containers will be in 
// sorted order based on the lower bound values of their intervals.  
class Span {
    private: 
        std::array<IntervalCollision, 2> inlineIntervals; // common case of one or two intervals
        std::shared_ptr<std::vector<IntervalCollision>> extraIntervals; // shared pointer for lazy initialization
        size_t intervalCount;
        bool disjoint; // true if span is representing multiple disjoint intervals
    public: 
        void addInterval(Collision& a, Collision& b);
};

#endif /* SPAN_H */