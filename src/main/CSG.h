#ifndef CSG_H
#define CSG_H

#include <cstdint>
#include <memory>
#include <vector>
#include "Geometry.h"
#include "vec3.h"
#include "Interval.h"

// Store a single node of the CSG tree with two objects to combine
class CSG : public Geometry {
    public:
        CSG();
        int32_t rayIntersect(Collision* hit, Ray ray, float tmin, float tmax);
    private:
        // Consider making the left and right operands Geometry& ?? 
        std::shared_ptr<Geometry> left;
        std::shared_ptr<Geometry> right; 
        Interval range; // empty if both left and right are geometric primitives
};

#endif /* CSG_H */