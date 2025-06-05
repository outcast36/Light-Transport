#include <sstream>
#include <iomanip>
#include "Span.h"

Span::Span(const Collision& entry, const Collision& exit)
      : entry(entry), exit(exit) {}

Span Span::invalid() {
    Collision dummy{vec3<double>(), vec3<double>(), 0.0};
    return Span(dummy, dummy);
}

std::string Span::printSpan() const {
    std::stringstream s;
    s << std::fixed << std::setprecision(3) << "[" << entry.t << ", " << exit.t << "]";
    return s.str();
}

// Member access 
Collision Span::getEntry() const { return entry; }
Collision Span:: getExit() const { return exit; }

// Update members
void Span::setExit(const Collision& updated) { exit = updated; }
void Span::setEntry(const Collision& updated) { entry = updated; }

Interval Span::asInterval() {
    return Interval(entry.t, exit.t);
}

Span mergeOverlap(const Span& a, const Span& b) {
    Collision entry = b.getEntry();
    if (closerToOrigin(a.getEntry(), entry)) entry = a.getEntry();
    Collision exit = b.getExit();
    if (closerToOrigin(exit, a.getExit())) exit = a.getExit();
    return Span(entry, exit);
}