#ifndef CSG_H
#define CSG_H

#include <cstdint>
#include <memory>
#include <vector>
#include "Geometry.h"
#include "vec3.h"
#include "Interval.h"

enum SetOperation{unions, intersect, difference};

// Store a single node of the CSG tree with two objects to combine
class CSG : public Geometry {
    public:
        CSG(std::shared_ptr<Geometry> left, std::shared_ptr<Geometry> right, SetOperation op);
        int32_t rayIntersect(Collision* hit, Ray ray, Interval& range);
    private:
        // Consider making the left and right operands Geometry& ?? 
        std::shared_ptr<Geometry> left;
        std::shared_ptr<Geometry> right; 
        SetOperation op;
};

#endif /* CSG_H */

//Structure of arbitrary csg object
//CSG( CSG(sphere, cube, intersect), CSG( CSG( cylinder, cylinder, unions), cylinder, unions), difference)