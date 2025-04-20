#include "Sphere.h"

Sphere::Sphere(vec3<double>& center, double radius) : center(center), radius(radius) {};

int32_t Sphere::rayIntersect(Span* hit, Ray ray, Interval range) {
    vec3<double> center_to_origin = ray.origin - this->center;
    double radius_squared = this->radius * this->radius;
    double inverse_radius = 1/this->radius;
    double a = ray.direction.lengthSquared();
    double inverse_a = 1/a;
    double half_b = dot(ray.direction, center_to_origin);
    double c = (center_to_origin.lengthSquared()) - radius_squared;
    double discriminant = (half_b * half_b) - (a * c); 
    if (discriminant < 0) return -1; // no intersection
    Collision entry, exit;
    entry.t = ((-half_b) - sqrt(discriminant)) * inverse_a; // t0
    exit.t = ((-half_b) + sqrt(discriminant)) * inverse_a; // t1
    Interval hitRange(entry.t, exit.t);
    if (!intersectInterval(range, hitRange).empty()) return -1; // valid quadratic solutions, but neither is in [tmin, tmax]
    entry.intersection = ray.origin + (entry.t * ray.direction);
    exit.intersection = ray.origin + (exit.t * ray.direction);
    entry.surface_normal = (entry.intersection - this->center) * inverse_radius;
    exit.surface_normal = (exit.intersection - this->center) * inverse_radius;
    hit->entry = entry;
    hit->exit = exit;
    return 0;
}