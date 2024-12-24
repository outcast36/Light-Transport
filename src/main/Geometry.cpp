#include <cstddef> 
#include <cstdint> 
#include <cmath>
#include "Geometry.h"

int32_t rayIntersect(Collision* hit, Ray ray, Sphere object) {
    double radius_squared = object.radius * object.radius;
    double inverse_radius = 1/object.radius;
    // coefficients from the quadratic equation used to solve for ray parameter t
    double a = ray.direction.lengthSquared();
    double inverse_a = 1/a;
    double half_b = dot(ray.direction, ray.origin - object.center);
    double c = (ray.origin - object.center).lengthSquared() - radius_squared;
    double discriminant = (half_b * half_b) - (a * c); 

    if (discriminant < 0) return -1; // no intersection
    vec3<double> intersection;
    // the closest interesection is with the smallest positive solution for t
    double t = ((-half_b) - sqrt(discriminant)) * inverse_a;
    // only compute t1 (the + solution to quadratic) if the other solution is negative
    if (t < 0) t = ((-half_b) + sqrt(discriminant)) * inverse_a; 
    intersection = ray.origin + (t * ray.direction);
    hit->intersection = intersection;
    hit->surface_normal = (intersection - object.center) * inverse_radius;
    hit->t = t;
    return 0;
}