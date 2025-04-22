#include "CSG.h"

CSG::CSG(std::shared_ptr<BaseObject> left, std::shared_ptr<BaseObject> right, SetOperation op) :
left(left), right(right), op(op) {};

// Implicit post order traversal of binary tree representing complex CSG object
int32_t CSG::rayIntersect(Span* hit, Ray ray, Interval range) {
    Span leftHit, rightHit;
    int32_t leftStatus = this->left->rayIntersect(&leftHit, ray, range);
    int32_t rightStatus = this->right->rayIntersect(&rightHit, ray, range);
    // Ray intersects neither object -- zero spans created
    if (leftStatus < 0 && rightStatus < 0) return -1; 
    // Ray intersects one or both objects -- apply boolean operation
    switch (this->op) {
        case unions:
            break;
        case intersect:
            if (leftStatus < 0 || rightStatus < 0) return -1;
            combined.range = intersectInterval(leftHit.range, rightHit.range);
            break;
        case difference:
            if (leftStatus < 0) return -1;
            if (rightStatus > 0) rightHit.surface_normal = -rightHit.surface_normal;
            // if right status is hit:
            // turn right operand inside out (hit.surface_normal *= -1)
            // combine with intersection?  (de morgan)
            combined.range = differenceInterval(leftHit.range, rightHit.range);
            if (combined.range.empty()) return -1;
            
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