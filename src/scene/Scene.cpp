#include "Scene.h"

Scene::Scene() {};

// currently without an acceleration structure -- linear search through objects 
int32_t Scene::rayIntersect(Span* hit, Ray ray, Interval range) {
    Span cur; 
    double closest_t = range.max;
    int32_t res=-1; // return -1 on no intersection
    for (const auto& surface : this->geometry_list) {
        // at least one of entry and exit points is in [tmin, closest_so_far]
        if (surface->rayIntersect(&cur, ray, Interval(range.min, closest_t))==0) {
            res = 0; // hit any object with t in [tmin, tmax]
            if (cur.entry.t > 0 && cur.entry.t < closest_t) hit->entry = cur.entry;
            else if (cur.exit.t > 0 && cur.exit.t < closest_t) hit->entry = cur.exit;
        }
    }
    return res;
}

void Scene::add(std::shared_ptr<BaseObject> item) {
    this->geometry_list.push_back(item);
}

void Scene::clearScene() {
    this->geometry_list.clear();
}