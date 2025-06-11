#include "Sphere.h"

Sphere::Sphere(vec3<double>& center, double radius) : center(center), radius(radius) {};

std::optional<std::vector<Span>> Sphere::rayIntersect(Ray& ray) {
    vec3<double> center_to_origin = ray.origin - this->center;
    double radius_squared = this->radius * this->radius;
    double inverse_radius = 1/this->radius;
    double a = ray.direction.lengthSquared();
    double inverse_a = 1/a;
    double half_b = dot(ray.direction, center_to_origin);
    double c = (center_to_origin.lengthSquared()) - radius_squared;
    double discriminant = (half_b * half_b) - (a * c); 
    if (discriminant < 0) return std::nullopt; // no intersection
    Collision entry, exit;
    entry.t = ((-half_b) - sqrt(discriminant)) * inverse_a; // t0
    entry.intersection = ray.origin + (entry.t * ray.direction);
    entry.surface_normal = (entry.intersection - center) * inverse_radius;
    exit.t = ((-half_b) + sqrt(discriminant)) * inverse_a; // t1
    exit.intersection = ray.origin + (exit.t * ray.direction);
    exit.surface_normal = (exit.intersection - center) * inverse_radius;
    Span res_span{entry, exit};
    std::vector<Span> res(1, res_span);
    return res;
}