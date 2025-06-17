#include <iostream>
#include <algorithm>
#include <iterator>
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
// Assume that neither collection A nor collection B are empty
std::vector<Span> mergeIntervalLists(std::vector<Span>& a, std::vector<Span>& b) {
    std::vector<Span> result;
    std::merge(a.begin(), a.end(), 
               b.begin(), b.end(), 
               std::back_inserter(result), 
               [](const Span& x, const Span& y) {
                   return x.getEntry().t < y.getEntry().t;
               });
    return result;
}

// Assume intervals is a collection of intervals which are sorted by start
// Assume intervals collection is non-empty
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