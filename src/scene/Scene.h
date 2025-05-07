#ifndef SCENE_H
#define SCENE_H

#include <cmath>
#include <vector>
#include <memory>
#include "scene/RaycastTarget.h"
#include "object/GFXBase.h"
#include "object/BaseObject.h"

// Aggregate a collection of objects -- interface only cares about a single intersection point
class Scene : public RaycastTarget {
    private: 
        std::vector<std::shared_ptr<BaseObject>> geometry_list; // list of objects in the scene
    public:
        Scene();
        std::optional<Collision> rayIntersect(Ray& ray, Interval range) override;
        void add(std::shared_ptr<BaseObject>); // push_back wrapper
        void clearScene();
};


#endif /* SCENE_H */