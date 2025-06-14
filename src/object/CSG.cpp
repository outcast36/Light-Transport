#include <iostream>
#include "CSG.h"

CSG::CSG(std::shared_ptr<BaseObject> left, std::shared_ptr<BaseObject> right) 
    : left(left), right(right) {}

Unions::Unions(std::shared_ptr<BaseObject> left, std::shared_ptr<BaseObject> right) 
    : CSG(left, right) {}

std::string printIntervalList(std::vector<Span>& items) {
    std::string output="";
    bool first = true;
    for (const auto& span:items) {
        if (!first) output+=", ";
        output += span.printSpan();
        first = false;
    }
    return output;
}

// Assume that both collections A and B are sorted by start and are both 
// pairwise disjoint. This function merges A and B into a single collection of
// intervals, which are sorted by start, but not necessarily pairwise disjoint. 
std::vector<Span> mergeIntervalLists(std::vector<Span>& a, std::vector<Span>& b) {
    uint8_t i = 0, j = 0;
    std::vector<Span> result;
    while (i < a.size() && j < b.size()) {
        Collision left_start = a[i].getEntry();
        Collision right_start = b[j].getEntry();

        if (closerToOrigin(left_start, right_start)) result.push_back(a[i++]);
        else result.push_back(b[j++]);
    }
    while (i < a.size()) result.push_back(a[i++]);
    while (j < b.size()) result.push_back(b[j++]);
    return result;
}

// Assume intervals is a collection of intervals which are sorted by start
std::vector<Span> mergeIntervals(std::vector<Span>& intervals) {
    u_int8_t i = 0;
    std::vector<Span> result;
    while (i < intervals.size()) {
        uint8_t j = i + 1;
        while (j < intervals.size() && closerOrTouching(intervals[j].getEntry(), intervals[i].getExit())) {
            intervals[i] = mergeOverlap(intervals[i], intervals[j]);
            ++j;
        }
        result.push_back(intervals[i]);
        i = j;
    }
    return result;
}

std::optional<std::vector<Span>> Unions::rayIntersect(Ray& ray) {
    auto leftIntervals = left->rayIntersect(ray);
    auto rightIntervals = right->rayIntersect(ray);
    // Neither child node is intersected
    if (!leftIntervals && !rightIntervals) {
        return std::nullopt; 
    }
    else if (!rightIntervals) return leftIntervals;
    else if (!leftIntervals) return rightIntervals;
    else {
        auto merged = mergeIntervalLists(*leftIntervals, *rightIntervals);
        return mergeIntervals(merged);
    }
}