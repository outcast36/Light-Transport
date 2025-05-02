#ifndef CSG_H
#define CSG_H

#include <memory>
#include "object/BaseObject.h"

// Store a single node of the CSG tree with two objects to combine
class CSG : public BaseObject {
 public:
  CSG(std::shared_ptr<BaseObject> left, std::shared_ptr<BaseObject> right);
  virtual ~CSG() = default; 
  virtual std::optional<IntervalSet> rayIntersect(Ray& ray, Interval range)=0;
 protected:
  std::shared_ptr<BaseObject> left;
  std::shared_ptr<BaseObject> right;
};

class Unions : public CSG {
 public: 
  std::optional<IntervalSet> rayIntersect(Ray& ray, Interval range) override;
};

class Intersect : public CSG {
 public: 
  std::optional<IntervalSet> rayIntersect(Ray& ray, Interval range) override;
};

class Difference : public CSG {
 public:
  std::optional<IntervalSet> rayIntersect(Ray& ray, Interval range) override;
};

#endif /* CSG_H */