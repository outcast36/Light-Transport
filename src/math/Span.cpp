#include "Span.h"

std::string Span::printSpan() const {
    return "[" + std::to_string(entry.t) + ", " + std::to_string(exit.t) + "]";  
}

// Member access 
Collision Span::getEntry() const { return entry; }
Collision Span:: getExit() const { return exit; }

// Update members
void Span::setExit(const Collision& updated) { exit = updated; }
void Span::setEntry(const Collision& updated) { entry = updated; }

void Span::mergeOverlap(const Span& other) {
    entry = std::min(entry, other.entry);
    exit = std::max(exit, other.exit);
}