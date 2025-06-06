#ifndef CSG_H
#define CSG_H

#include <memory>
#include "BaseObject.h"

// Store a single node of the CSG tree with two objects to combine
class CSG : public BaseObject {
 public:
  CSG(std::shared_ptr<BaseObject> left, std::shared_ptr<BaseObject> right);
  virtual ~CSG() = default; 
  virtual std::optional<std::vector<Span>> rayIntersect(Ray& ray)=0;
 protected:
  std::shared_ptr<BaseObject> left;
  std::shared_ptr<BaseObject> right;
};

std::string printIntervalList(std::vector<Span>& items);
std::vector<Span> join(std::vector<Span>& a, std::vector<Span>& b); // union operation
std::vector<Span> intersection(std::vector<Span>& a, std::vector<Span>& b); // intersection operation
std::vector<Span> subtract(std::vector<Span>& a, std::vector<Span>& b); // difference operation

class Unions : public CSG {
 public: 
  std::optional<std::vector<Span>> rayIntersect(Ray& ray) override;
};

class Intersect : public CSG {
 public: 
  std::optional<std::vector<Span>> rayIntersect(Ray& ray) override;
};

class Difference : public CSG {
 public:
  std::optional<std::vector<Span>> rayIntersect(Ray& ray) override;
};

#endif /* CSG_H */