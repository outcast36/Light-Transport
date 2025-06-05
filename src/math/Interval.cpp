#include <limits>
#include <algorithm>
#include "Interval.h"

// Empty constructor creates empty interval
Interval::Interval() : min(std::numeric_limits<double>::max()), max(-std::numeric_limits<double>::max()) {};
Interval::Interval(double start, double end) : start(start), end(end) {};
double Interval::size() const {
    return this->end - this->start;
};

bool Interval::empty() const {
    return this->start > this->end;
}

// Check if t in [start, end]
bool Interval::contains(double t) const {
    return this->start <= t && t <= this->end;
}; 

// Check if t in (start, end)
bool Interval::exclusiveContains(double t) const {
    return this->start < t && t < this->end;
};