#include <cmath>
#include <iostream>
#include "Cameras.h"

// camera constructor sets image dimensions
Camera::Camera(uint32_t width, uint32_t height) : img_width(width), img_height(height) {}

/*
Canonical perspective camera:
eye is at the origin, image plane basis vectors (u_axis, v_axis) are parallel to positive x,y axes
viewport is a 1x1 square and the image plane is distance 1 from the camera eye. The VFOV angle
given this camera pose is approximately 52 degrees. 
*/
PerspectiveCamera::PerspectiveCamera(uint32_t width, uint32_t height) : Camera(width,  height) {
    eye = vec3<double>(0,0,0);
    u_axis = vec3<double>(1,0,0);
    v_axis = vec3<double>(0,1,0);
    w_axis = vec3<double>(0,0,1);
    aspect_ratio = 1.0;
    vfov = 0.927295; // vfov given focal length=1, vw=1, vh=1, roughly 52 degrees
    focal_length = 1.0;
}

Ray PerspectiveCamera::pixelToRay(int32_t i, int32_t j) {
    double viewport_height = 2 * this->focal_length* tan(this->vfov/2);
    double viewport_width = viewport_height * this->aspect_ratio;
    double u = viewport_width * (((j+0.5)/this->img_width) - 0.5);
    double v = viewport_height * (((i+0.5)/this->img_height) - 0.5);
    vec3<double> direction = (u * this->u_axis) + (v * this->v_axis) - (this->focal_length * this->w_axis);
    direction = unitVector(direction);
    return Ray{this->eye, direction};
}