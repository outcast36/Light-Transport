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

Plane::Plane(vec3<double>& point, vec3<double>& normal) : point(point), normal(normal) {};

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

Cylinder::Cylinder(vec3<double>& axis, vec3<double>& point, double height, double radius) : 
axis_of_rotation(axis), point_in_center(point), height(height), radius(radius) {};

int32_t Cylinder::rayIntersect(Collision* hit, Ray ray, float tmin, float tmax) {   
    vec3<double> axis_to_origin = ray.origin - this->point_in_center;
    double regularization = dot(this->axis_of_rotation, axis_to_origin);
    double dir_projection = dot(this->axis_of_rotation, ray.direction);
    double radius_squared = this->radius * this->radius;
    double inverse_radius = 1/this->radius;
    double a = dot(ray.direction, ray.direction) - (dir_projection * dir_projection);
    double inverse_a = 1/a;
    double half_b = dot(ray.direction, axis_to_origin) - (regularization * dir_projection);
    double c = axis_to_origin.lengthSquared() - (regularization * regularization) - radius_squared;
    double discriminant = (half_b * half_b) - (a * c); 
    if (discriminant < 0) return -1; // no intersection
    vec3<double> intersection;
    // the closest interesection is with the smallest positive solution for t
    double t = ((-half_b) - sqrt(discriminant)) * inverse_a;
    // only compute t1 (the + solution to quadratic) if the other solution is negative
    if (t < 0) t = ((-half_b) + sqrt(discriminant)) * inverse_a; 
    if (t < tmin || t > tmax) return -1; // solution to quadratic is valid, but not in search interval
    intersection = ray.origin + (t * ray.direction);
    vec3<double> axis_to_intersection = intersection - this->point_in_center;
    vec3<double> projection = dot(axis_to_intersection, this->axis_of_rotation) * this->axis_of_rotation;
    hit->intersection = intersection;
    hit->surface_normal = (axis_to_intersection - projection) * inverse_radius;
    hit->t = t;
    return 0;
}

Cone::Cone(vec3<double>& axis, vec3<double>& apex, double height, double theta) :
axis_of_rotation(axis), apex(apex), height(height), theta(theta) {};

int32_t Cone::rayIntersect(Collision* hit, Ray ray, float tmin, float tmax) {
    vec3<double> axis_to_origin = ray.origin - this->apex;
    double regularization = dot(this->axis_of_rotation, axis_to_origin);
    double dir_projection = dot(this->axis_of_rotation, ray.direction);
    double cosine_squared = cos(this->theta) * cos(this->theta);
    double a = (cosine_squared * dot(ray.direction, ray.direction)) - (dir_projection * dir_projection);
    double inverse_a = 1/a;
    double half_b = (cosine_squared * dot(ray.direction, axis_to_origin)) - (regularization * dir_projection);
    double c = cosine_squared * axis_to_origin.lengthSquared() - (regularization * regularization);
    double discriminant = (half_b * half_b) - (a * c); 
    if (discriminant < 0) return -1; // no intersection
    vec3<double> intersection;
    // the closest interesection is with the smallest positive solution for t
    double t = ((-half_b) - sqrt(discriminant)) * inverse_a;
    // only compute t1 (the + solution to quadratic) if the other solution is negative
    if (t < 0) t = ((-half_b) + sqrt(discriminant)) * inverse_a; 
    if (t < tmin || t > tmax) return -1; // solution to quadratic is valid, but not in search interval
    intersection = ray.origin + (t * ray.direction);
    vec3<double> axis_to_intersection = intersection - this->apex;
    if (dot(axis_to_intersection, this->axis_of_rotation) < 0) return -1; // only take the same half cone pointing with axis vector
    vec3<double> projection = dot(axis_to_intersection, this->axis_of_rotation) * this->axis_of_rotation;
    hit->intersection = intersection;
    
    // TODO Calculate normals correctly
    hit->surface_normal = unitVector(axis_to_intersection - projection);
    hit->t = t;
    return 0;
}
