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