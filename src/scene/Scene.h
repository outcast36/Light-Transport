#ifndef SCENE_H
#define SCENE_H

#include <cmath>
#include <vector>
#include <memory>
#include "object/BaseObject.h"
#include "object/GFXBase.h"

// List of geometric objects, wrap the closest intersection method as a rayIntersect implementation 
class Scene : public BaseObject {
    public:
        Scene();
        int32_t rayIntersect(Span* hit, Ray ray, Interval range);
        void add(std::shared_ptr<BaseObject>); // push_back wrapper
        void clearScene();
        std::vector<std::shared_ptr<BaseObject>> geometry_list; // list of objects in the scene
};


#endif /* SCENE_H */