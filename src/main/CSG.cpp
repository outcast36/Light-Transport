#include "CSG.h"
#include <iostream>

CSG::CSG(std::shared_ptr<Geometry> left, std::shared_ptr<Geometry> right, SetOperation op) :
left(left), right(right), op(op) {};

// Implicit post order traversal of binary tree representing complex CSG object
int32_t CSG::rayIntersect(Collision* hit, Ray ray, Interval& range) {
    Collision leftHit, rightHit, combined;
    int32_t leftStatus, rightStatus;
    leftStatus = this->left->rayIntersect(&leftHit, ray, range);
    rightStatus = this->right->rayIntersect(&rightHit, ray, range);

    // Ray intersects neither object
    if (leftStatus < 0 && rightStatus < 0) return -1; 
    // Ray intersects one or both objects -- apply boolean operation
    switch (this->op) {
        case unions:
            // Ray intersects only one object
            if (leftStatus < 0) {
                *hit = rightHit;
                return 0;
            } 
            else if (rightStatus < 0) {
                *hit = leftHit;
                return 0;
            }
            combined.range = unionInterval(leftHit.range, rightHit.range);
            break;
        case intersect:
            if (leftStatus < 0 || rightStatus < 0) return -1;
            combined.range = intersectInterval(leftHit.range, rightHit.range);
            break;
        // TODO make difference actually work
        // Additional work needs to be done on calculating surface normals
        case difference:
            if (leftStatus < 0) return -1;
            combined.range = differenceInterval(leftHit.range, rightHit.range);
            if (combined.range.empty()) return -1;
            std::cout << "Left interval: " << leftHit.range.min << " " << leftHit.range.max << std::endl;
            std::cout << "Right interval: " << rightHit.range.min << " " << rightHit.range.max << std::endl;
            std::cout << "Difference interval: " << combined.range.min << " " << combined.range.max << std::endl;
            break;
    }    
    double t = (combined.range.min > 0) ? combined.range.min : combined.range.max;
    if (!range.contains(t)) return -1;
    combined.t = t;
    vec3<double> intersection = ray.origin + (t * ray.direction);
    combined.intersection = intersection;
    vec3<double> surface_normal;
    if (t == leftHit.range.min || t == leftHit.range.max) surface_normal = leftHit.surface_normal;
    else surface_normal = rightHit.surface_normal;
    combined.surface_normal = surface_normal;
    *hit = combined;
    return 0;
}