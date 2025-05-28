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

Span mergeOverlap(const Span& a, const Span& b) {
    Collision entry = std::min(a.getEntry(), b.getEntry());
    Collision exit = std::max(a.getExit(), b.getExit());
    return Span(entry, exit);
}