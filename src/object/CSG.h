#ifndef CSG_H
#define CSG_H

#include <memory>
#include "BaseObject.h"

enum SetOperation{unions, intersect, difference};

// Store a single node of the CSG tree with two objects to combine
class CSG : public BaseObject {
    public:
        CSG(std::shared_ptr<BaseObject> left, std::shared_ptr<BaseObject> right, SetOperation op);
        int32_t rayIntersect(Span* hit, Ray ray, Interval range);
    private:
        Span head; // head of possible linked list of disjoint intervals
        std::shared_ptr<BaseObject> left;
        std::shared_ptr<BaseObject> right; 
        SetOperation op;
};

#endif /* CSG_H */