#ifndef INTERVAL_H
#define INTERVAL_H

class Interval {
    public: 
        Interval();
        Interval(double min, double max);
        double size() const;
        bool contains(double t) const; // check if t in [min, max]
        bool exclusiveContains(double t) const; // check if t in (min, max)
        double min;
        double max;
};

#endif /* INTERVAL_H */