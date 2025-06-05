#ifndef INTERVAL_H
#define INTERVAL_H

class Interval {
 public: 
  Interval();
  Interval(double start, double end);
  double size() const;
  bool empty() const; 
  bool contains(double t) const; // check if t in [start, end]
  bool exclusiveContains(double t) const; // check if t in (start, end)
  double start;
  double end;
};

#endif /* INTERVAL_H */