#include <algorithm>
#include <cstdint>
#include <iostream>
#include "object/IntervalSet.h"

IntervalSet::IntervalSet()
    : inlineIntervals({Span::invalid(), Span::invalid()}), 
    extraIntervals(0), 
    intervalCount(0) {}

IntervalSet::IntervalSet(const Span& single) 
    : inlineIntervals({single, Span::invalid()}), 
      extraIntervals(0),
      intervalCount(1) {}

IntervalSet::IntervalSet(const std::array<Span,2>& inlines)
    : inlineIntervals(inlines),
      extraIntervals(0),
      intervalCount(2) {}

IntervalSet IntervalSet::empty() {
    return IntervalSet();
}

IntervalSet IntervalSet::fromSingleSpan(Span& primitive) {
    return IntervalSet(primitive);
}

// Union Operation
void join(IntervalSet& other) {
    // add all intervals from other and merge any overlaps while keeping 
    // the entire collection sorted by entry.t
    for (const auto& interval:other) {
        std::cout << '(' << interval.getEntry() << ' ' << interval.getExit() << ')\n';
    }
} 

void intersection(IntervalSet& other) {
    /*
    for each interval in caller object:
        for each interval in other object: 
            apply binary intersection operation
            [max(entry), min(exit)]
            if intersection is empty then dont include in result
    no need to worry about intersections overlapping due to mutual exclusivity 
    of each intervalset operand
    */
}

// Difference Operation
void subtract(IntervalSet& other) {
    /*
    erm demorgan laws? 
    becomes string of intersections of complements of each interval in other
    do complement and intersect 
    caller object union (complement argument object)
    */
} 