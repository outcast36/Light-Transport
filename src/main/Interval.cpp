#include <limits>
#include <algorithm>
#include <iostream>
#include "Interval.h"

// Empty constructor creates empty interval
Interval::Interval() : min(std::numeric_limits<double>::max()), max(-std::numeric_limits<double>::max()) {};
Interval::Interval(double min, double max) : min(min), max(max) {};
double Interval::size() const {
    return this->max - this->min;
};

bool Interval::empty() const {
    return this->min > this->max;
}

// Check if t in [min, max]
bool Interval::contains(double t) const {
    return this->min <= t && t <= this->max;
}; 

// Check if t in (min, max)
bool Interval::exclusiveContains(double t) const {
    return this->min < t && t < this->max;
}; 


Interval unionInterval(Interval& a, Interval& b) {
    double start = std::min(a.min, b.min);
    double end = std::max(a.max, b.max);
    return Interval(start, end);
}

Interval intersectInterval(Interval& a, Interval& b) {
    double start = std::max(a.min, b.min);
    double end = std::min(a.max, b.max);
    return Interval(start, end);
}

// A - B
Interval differenceInterval(Interval& a, Interval& b) {
    if (a.empty() || b.empty() || intersectInterval(a, b).empty()) return a; 
    // Return empty interval when A interval is equal to or inside of B interval
    if (a.min >= b.min && a.max <= b.max) return Interval();
    // Difference interval A - B is completely to the right of B interval
    else if (a.min >= b.min && a.max > b.max) return Interval(b.max, a.max);
    // Difference interval A - B is completely to the left of B interval
    else if (a.min < b.min && a.max <= b.max) return Interval(a.min, b.min);
    // Difference interval A - B splits the A interval into two sections
    // Return closer of the two difference intervals with a min value > 0
    else {
        if (a.min > 0) return Interval(a.min, b.min);
        else return Interval(a.max, b.max);
    }
}
