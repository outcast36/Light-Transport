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

// Union operation
std::vector<Span> mergeIntervalLists(std::vector<Span>& a, std::vector<Span>& b);
std::vector<Span> mergeIntervals(std::vector<Span>& intervals);

class Unions : public CSG {
 public: 
  Unions(std::shared_ptr<BaseObject> left, std::shared_ptr<BaseObject> right);
  std::optional<std::vector<Span>> rayIntersect(Ray& ray) override;
};

#endif /* CSG_H */