#ifndef MODELS_H
#define MODELS_H

#include <memory>
#include "vec3.h"
#include "Geometry.h"
#include "Shapes.h"

// For now assume all lambertian -- bundle albedo with geometry
class Model {
    public:
        Model(vec3<float>& albedo, Shape& geometry) : albedo(albedo), geometry(geometry) {};
        vec3<float> albedo;
        Shape& geometry; // unique_ptr<Shape>??
};

#endif /* MODELS_H */