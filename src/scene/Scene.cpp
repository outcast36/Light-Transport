#include "Scene.h"

Scene::Scene() {};

// currently without an acceleration structure -- linear search through objects 

// Assumption: This can always return the first interval in an interval set
// since primitives and composite CSG objects will only return intervals
// in [tmin, tmax] interval
std::optional<Collision> Scene::rayIntersect(Ray& ray, Interval range) {
    Collision cur_closest;
    double closest_t = range.end;
    bool hit_anything = false;
    for (const auto& surface : geometry_list) {
        auto result = surface->rayIntersect(ray);
        if (result != std::nullopt) {
            auto intervals = (*result);
            uint8_t i = 0;
            while (i < intervals.size()) {
                if (range.exclusiveContains(intervals[i].getEntry().t)) {
                    cur_closest = intervals[i].getEntry();
                    hit_anything = true;
                } 
                else if (range.exclusiveContains(intervals[i].getExit().t)) {
                    cur_closest = intervals[i].getExit();
                    hit_anything = true;
                } 
                ++i;
            }
        }
        range.end = closest_t;
    }
    if (hit_anything) return cur_closest;
    else return std::nullopt;
}

void Scene::add(std::shared_ptr<BaseObject> item) {
    this->geometry_list.push_back(item);
}

void Scene::clearScene() {
    this->geometry_list.clear();
}