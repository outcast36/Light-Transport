#ifndef SPHERE_H
#define SPHERE_H

#include <cmath>
#include "BaseObject.h"

class Sphere : public BaseObject {
 public:
  Sphere(vec3<double>& center, double radius);
  std::optional<IntervalSet> rayIntersect(Ray& ray, Interval range) override;
 
 private: 
  vec3<double> center;
  double radius;
};

#endif /* SPHERE_H */