#include <limits>
#include <algorithm>
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
    // Case where A interval is completely inside the B interval, return empty interval
    if (a.min >= b.min && a.max <= b.max) return Interval();
    // Case where B interval splits A interval
    else if (b.min > a.min && b.max < a.max) {
        if (a.min > 0) return Interval(a.min, b.min);
        else return Interval(b.max, a.max);
    }
    else if (a.min < b.min) return Interval(a.min, b.min);
    else return Interval(b.max, a.max);
}
