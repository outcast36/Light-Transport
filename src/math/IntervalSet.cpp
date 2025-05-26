#include <algorithm>
#include <cstdint>
#include "IntervalSet.h"

IntervalSet::IntervalSet()
    : inlineIntervals({Span::invalid(), Span::invalid()}),  
    intervalCount(0) {}

IntervalSet::IntervalSet(const Span& single) 
    : inlineIntervals({single, Span::invalid()}), 
      intervalCount(1) {}

IntervalSet::IntervalSet(const std::array<Span,2>& inlines)
    : inlineIntervals(inlines),
      intervalCount(2) {}

IntervalSet IntervalSet::empty() {
    return IntervalSet();
}

IntervalSet IntervalSet::fromSingleSpan(Span& primitive) {
    return IntervalSet(primitive);
}

std::string IntervalSet::printIntervalSet() {
    std::string output="";
    bool first = true;
    for (auto it=begin(); it!=end(); ++it) {
        if (!first) output+=" ";
        output += (*it).printSpan();
        first = false;
    }
    return output;
}

void IntervalSet::push_back(Span& new_interval) {
    if (intervalCount<2) inlineIntervals[intervalCount] = new_interval;
    else extraIntervals.push_back(new_interval);
    ++intervalCount;
}

void IntervalSet::clear() {
    inlineIntervals[0] = Span::invalid();
    inlineIntervals[1] = Span::invalid();
    if (intervalCount>2) extraIntervals.clear();
    intervalCount = 0;
}

// Union Operation
// TODO Change these to be join(set a, set b) rather than methods so intent is clearer
void IntervalSet::join(IntervalSet& other) {
    IntervalSet::Iterator middle = other.end();
    IntervalSet::Iterator cur = begin();
    while (cur!=end()) {
        other.push_back(*cur);
        ++cur;
    }
    std::inplace_merge(
        other.begin(), 
        middle, 
        other.end(),
        [](const Span& a, const Span& b) {
        return a.getEntry() < b.getEntry(); }
    );
    clear();
    cur = other.begin();
    while (cur != other.end()) {
        if (isEmpty() || (*back()).getExit() < (*cur).getEntry()) push_back(*cur);
        else (*back()).mergeOverlap(*cur);
        ++cur;
    }
} 

void IntervalSet::intersection(IntervalSet& other) {
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
void IntervalSet::subtract(IntervalSet& other) {
    /*
    erm demorgan laws? 
    becomes string of intersections of complements of each interval in other
    do complement and intersect 
    caller object union (complement argument object)
    */
} 