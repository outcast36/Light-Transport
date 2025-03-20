#include <cstddef> 
#include <cstdint> 
#include <cmath>
#include "Geometry.h"

constexpr double pi = M_PI;

Scene::Scene() {};

// currently without an acceleration structure -- linear search through objects 
int32_t Scene::rayIntersect(Collision* hit, Ray ray, Interval& range) {
    Collision cur;
    double closest_t = range.max;
    int32_t res=-1; // return -1 on no intersection
    for (const auto& surface : this->geometry_list) {
        if (surface->rayIntersect(&cur, ray, range)==0) {
            res = 0; // hit any object with t in [tmin, tmax]
            if (cur.t < closest_t && range.contains(cur.t)) *hit = cur; 
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

int32_t Sphere::rayIntersect(Collision* hit, Ray ray, Interval& range) {
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
    // Compute intersection interval
    double t0 = ((-half_b) - sqrt(discriminant)) * inverse_a;
    double t1 = ((-half_b) + sqrt(discriminant)) * inverse_a;
    double t = (t0 > 0) ? t0 : t1;
    Interval hitRange(t0,t1);
    if (!range.contains(t)) return -1; // solution to quadratic is valid, but not in search interval
    vec3<double> intersection = ray.origin + (t * ray.direction);
    hit->intersection = intersection;
    hit->surface_normal = (intersection - this->center) * inverse_radius;
    hit->t = t;
    hit->range = hitRange;
    return 0;
}

Plane::Plane(vec3<double>& point, vec3<double>& normal) : point(point), normal(normal) {};

int32_t Plane::rayIntersect(Collision* hit, Ray ray, Interval& range) {
    double denominator = dot(this->normal, ray.direction);
    if (denominator == 0.0) return -1; // floating point accuracy?
    denominator = 1/denominator;
    vec3<double> in_plane = (ray.origin - this->point);
    double t = -dot(this->normal, in_plane) * denominator;
    if (!range.contains(t)) return -1;
    hit->intersection = ray.origin + (t * ray.direction);
    hit->surface_normal = this->normal;
    hit->t = t;
    return 0;
}

Disc::Disc() {};

Disc::Disc(vec3<double>& point, vec3<double>& normal, double radius) : 
center(point), normal(normal), radius(radius) {};

int32_t Disc::rayIntersect(Collision* hit, Ray ray, Interval& range) {
    Plane p(this->center, this->normal);
    if (p.rayIntersect(hit, ray, range) < 0) return -1;
    else {
        vec3<double> in_plane = hit->intersection - this->center;
        if (in_plane.length() > this->radius) return -1;
    }
    return 0;
}

Cylinder::Cylinder(vec3<double>& axis, vec3<double>& point, double height, double radius) : 
axis_of_rotation(axis), point_in_center(point), radius(radius) {
    vec3<double> bot_normal = -axis;
    vec3<double> top_center = point + (height * axis);
    bot = Disc(point, bot_normal, radius);
    top = Disc(top_center, axis, radius);
    heightBounds = Interval(0, height);
};

int32_t Cylinder::rayIntersect(Collision* hit, Ray ray, Interval& range) {  
    double bot_hit_param = -1, top_hit_param = -1;
    if (this->bot.rayIntersect(hit, ray, range)==0) bot_hit_param = hit->t;
    if (this->top.rayIntersect(hit, ray, range)==0) top_hit_param = hit->t;
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
    if (discriminant < 0) return -1; // no intersection cap or shell

    double t0 = ((-half_b) - sqrt(discriminant)) * inverse_a;
    double t1 = ((-half_b) + sqrt(discriminant)) * inverse_a;
    vec3<double> int_t0 = ray.origin + (t0 * ray.direction);
    double proj_t0 = dot((int_t0 - this->point_in_center), this->axis_of_rotation);
    double t = (t0 > 0 && this->heightBounds.contains(proj_t0)) ? t0 : t1; 
    if (!range.contains(t)) return -1; // check interval [tmin, tmax]
    vec3<double> intersection = ray.origin + (t * ray.direction);
    vec3<double> axis_to_intersection = (intersection - this->point_in_center);
    double projection_len = dot(axis_to_intersection, this->axis_of_rotation);
    vec3<double> projection = projection_len * this->axis_of_rotation;

    // Intersect shell beyond past either plane capping the height of the cylinder
    if (!this->heightBounds.contains(projection_len) && bot_hit_param<0 && top_hit_param<0) return -1;
    if (bot_hit_param > 0 && top_hit_param > 0) hit->range = Interval(std::min(bot_hit_param, top_hit_param), std::max(bot_hit_param, top_hit_param));
    else if (bot_hit_param >= 0) hit->range = Interval(std::min(bot_hit_param, t), std::max(bot_hit_param, t));  
    else if (top_hit_param >= 0) hit->range = Interval(std::min(top_hit_param, t), std::max(top_hit_param, t));
    else hit->range = Interval(t0,t1);
    hit->t = hit->range.min;
    if (hit->t==bot_hit_param) hit->surface_normal = -this->axis_of_rotation;
    else if (hit->t==top_hit_param) hit->surface_normal = this->axis_of_rotation;
    else if (hit->t==t) hit->surface_normal = (axis_to_intersection - projection) * inverse_radius;
    hit->intersection = ray.origin + (hit->t * ray.direction);
    return 0;
}

Cone::Cone(vec3<double>& axis, vec3<double>& apex, double height, double theta) :
axis_of_rotation(axis), apex(apex), height(height), theta(theta) {};

int32_t Cone::rayIntersect(Collision* hit, Ray ray, Interval& range) {
    vec3<double> axis_to_origin = ray.origin - this->apex;
    double regularization = dot(this->axis_of_rotation, axis_to_origin);
    double dir_projection = dot(this->axis_of_rotation, ray.direction);
    double cosine = cos(this->theta);
    double cosine_squared = cosine * cosine;
    double a = (cosine_squared * dot(ray.direction, ray.direction)) - (dir_projection * dir_projection);
    double inverse_a = 1/a;
    double half_b = (cosine_squared * dot(ray.direction, axis_to_origin)) - (regularization * dir_projection);
    double c = cosine_squared * axis_to_origin.lengthSquared() - (regularization * regularization);
    double discriminant = (half_b * half_b) - (a * c); 
    if (discriminant < 0) return -1; // no intersection
    // Compute intersection interval
    double t0 = ((-half_b) - sqrt(discriminant)) * inverse_a;
    double t1 = ((-half_b) + sqrt(discriminant)) * inverse_a;
    double t = (t0 > 0) ? t0 : t1;
    Interval hitRange(t0,t1);
    if (!range.contains(t)) return -1; // solution to quadratic is valid, but not in search interval
    vec3<double> intersection = ray.origin + (t * ray.direction);
    vec3<double> axis_to_intersection = intersection - this->apex;
    double projection_len = dot(axis_to_intersection, this->axis_of_rotation);
    // TODO change this to single interval contains check
    if (dot(axis_to_intersection, this->axis_of_rotation) < 0) return -1; // only take the same half cone pointing with axis vector
    // only instersect if the length of the projection to the rotation axis is in [0,h]
    if (abs(projection_len) > this->height) return -1; // height bound 
    
    // how to intersect disc where projection length == height

    vec3<double> projection = dot(axis_to_intersection, this->axis_of_rotation) * this->axis_of_rotation;
    vec3<double> gradient = this->axis_of_rotation - (cosine * unitVector(axis_to_intersection));
    hit->intersection = intersection;
    hit->surface_normal = -unitVector(gradient);
    hit->t = t;
    hit->range = hitRange;
    return 0;
}
