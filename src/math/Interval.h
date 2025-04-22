#ifndef INTERVAL_H
#define INTERVAL_H

class Interval {
    public: 
        Interval();
        Interval(double min, double max);
        double size() const;
        bool empty() const; 
        bool contains(double t) const; // check if t in [min, max]
        bool exclusiveContains(double t) const; // check if t in (min, max)
        double min;
        double max;
};

// Set operations for combining CSG objects, 
Interval unionInterval(Interval& a, Interval& b);
Interval intersectInterval(Interval& a, Interval& b);
Interval differenceInterval(Interval& a, Interval& b);

#endif /* INTERVAL_H */