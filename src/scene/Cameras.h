#ifndef CAMERAS_H
#define CAMERAS_H

#include <cstdint>
#include "GFXBase.h"

class Camera {
    protected:
        vec3<double> eye;
        vec3<double> u_axis;
        vec3<double> v_axis;
        vec3<double> w_axis;
        double aspect_ratio;  
        uint32_t img_width;
        uint32_t img_height;
    public: 
        Camera(uint32_t width, uint32_t height);
        virtual Ray pixelToRay(int32_t i, int32_t j) = 0; // pure virtual function
};

class PerspectiveCamera : public Camera {
    public: 
        PerspectiveCamera(uint32_t width, uint32_t height); // empty constructor makes a canonical camera
        Ray pixelToRay(int32_t i, int32_t j); 
    private: 
        // this angle implicitly defines the viewport dimensions along with aspect ratio
        double vfov; // given in radians
        double focal_length; // distance to image plane in ray tracing model
};

#endif /* CAMERAS_H */