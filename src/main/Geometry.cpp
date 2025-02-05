#include <cstddef> 
#include <cstdint> 
#include <cmath>
#include "Geometry.h"

Scene::Scene() {};

// currently without an acceleration structure -- linear search through objects 
int32_t Scene::rayIntersect(Collision* hit, Ray ray, float tmin, float tmax) {
    Collision cur;
    double closest_t = tmax;
    int32_t res=-1; // return -1 on no intersection
    for (const auto& surface : this->geometry_list) {
        if (surface->rayIntersect(&cur, ray, tmin, tmax)==0) {
            res = 0; // hit any object with t in [tmin, tmax]
            if (cur.t < closest_t && tmin <= cur.t && cur.t <= tmax) *hit = cur;
        }
    }
    return res;
}

void Scene::add(std::shared_ptr<Geometry> item) {
    this->geometry_list.push_back(item);
}

void Scene::clearScene() {
    this->geometry_list.clear();
}

Sphere::Sphere(vec3<double>& center, double radius) : center(center), radius(radius) {};

int32_t Sphere::rayIntersect(Collision* hit, Ray ray, float tmin, float tmax) {
    vec3<double> center_to_origin = ray.origin - this->center;
    double radius_squared = this->radius * this->radius;
    double inverse_radius = 1/this->radius;
    // coefficients from the quadratic equation used to solve for ray parameter t
    double a = ray.direction.lengthSquared();
    double inverse_a = 1/a;
    double half_b = dot(ray.direction, center_to_origin);
    double c = (center_to_origin.lengthSquared()) - radius_squared;
    double discriminant = (half_b * half_b) - (a * c); 
    if (discriminant < 0) return -1; // no intersection
    vec3<double> intersection;
    // the closest interesection is with the smallest positive solution for t
    double t = ((-half_b) - sqrt(discriminant)) * inverse_a;
    // only compute t1 (the + solution to quadratic) if the other solution is negative
    if (t < 0) t = ((-half_b) + sqrt(discriminant)) * inverse_a; 
    if (t < tmin || t > tmax) return -1; // solution to quadratic is valid, but not in search interval
    intersection = ray.origin + (t * ray.direction);
    hit->intersection = intersection;
    hit->surface_normal = (intersection - this->center) * inverse_radius;
    hit->t = t;
    return 0;
}

int32_t Plane::rayIntersect(Collision* hit, Ray ray, float tmin, float tmax) {
    double denominator = dot(this->normal, ray.direction);
    if (denominator == 0.0) return -1; // floating point accuracy?
    denominator = 1/denominator;
    vec3<double> in_plane = (this->point - ray.origin);
    double t = dot(this->normal, in_plane) * denominator;
    if (t < tmin || t > tmax) return -1;
    hit->intersection = ray.origin + (t * ray.direction);
    hit->surface_normal = this->normal;
    return 0;
}

int32_t Cylinder::rayIntersect(Collision* hit, Ray ray, float tmin, float tmax) {
    vec3<double> axis_to_origin = ray.origin - this->point_in_center;
    vec3<double> scaled_rotation_axis = dot(ray.direction, axis_of_rotation) * this->axis_of_rotation;
    double radius_squared = this->radius * this->radius;
    double inverse_radius = 1/this->radius;
    double regularization = dot(axis_of_rotation, axis_to_origin) * dot(axis_of_rotation, axis_to_origin);
    double a = dot(ray.direction, ray.direction - this->axis_of_rotation);
    double inverse_a = 1/a;
    double half_b = dot(axis_to_origin, ray.direction - scaled_rotation_axis);
    double c = dot(axis_to_origin, axis_to_origin) - regularization - radius_squared;
    double discriminant = (half_b * half_b) - (a * c); 

    if (discriminant < 0) return -1; // no intersection
    // the closest interesection is with the smallest positive solution for t
    double t = ((-half_b) - sqrt(discriminant)) * inverse_a;
    // only compute t1 (the + solution to quadratic) if the other solution is negative
    if (t < 0) t = ((-half_b) + sqrt(discriminant)) * inverse_a; 
    if (t < tmin || t > tmax) return -1;
    vec3<double> intersection;
    intersection = ray.origin + (t * ray.direction);
    vec3<double> intersection_to_axis = intersection - point_in_center;
    double projection_length = dot(intersection_to_axis, this->axis_of_rotation);
    vec3<double> orthogonal_component = intersection_to_axis - (projection_length * this->axis_of_rotation);
    hit->intersection = intersection;
    hit->surface_normal = orthogonal_component * inverse_radius;
    hit->t = t;
    return 0;
}