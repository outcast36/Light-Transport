#include "CSG.h"

CSG::CSG(std::shared_ptr<BaseObject> left, std::shared_ptr<BaseObject> right) 
    : left(left), right(right) {};

std::optional<IntervalSet> Unions::rayIntersect(Ray& ray, Interval range) {
    auto leftIntervals = left->rayIntersect(ray, range);
    auto rightIntervals = right->rayIntersect(ray, range);
    // Neither child node is intersected
    if (!leftIntervals && !rightIntervals) {
        return std::nullopt; 
    }
    else {
        (*leftIntervals).join(*rightIntervals);
        return leftIntervals;
    }
}

std::optional<IntervalSet> Intersect::rayIntersect(Ray& ray, Interval range) {
    auto left_intervals = left->rayIntersect(ray, range);
    auto right_intervals = right->rayIntersect(ray, range);
    // One or both child nodes doesn't intersect
    if (!left_intervals || !right_intervals) {
        return std::nullopt; 
    }
    else {
        (*left_intervals).intersection(*right_intervals);
    }
}

std::optional<IntervalSet> Difference::rayIntersect(Ray& ray, Interval range) {
    auto left_intervals = left->rayIntersect(ray, range);
    auto right_intervals = right->rayIntersect(ray, range);
    // Miss left node -- the minuend
    if (!left_intervals) {
        return std::nullopt;
    }
    else {
        // Check for intersection with subtrahend to perform subtraction
        if (right_intervals) (*left_intervals).subtract(*right_intervals);
        return left_intervals;
    }
}