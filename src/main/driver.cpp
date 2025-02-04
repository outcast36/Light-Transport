#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <chrono>
#include "FileHandle.h"
#include "PFMImageIO.h"
#include "vec3.h"
#include "Geometry.h"
#include "GFXBase.h"
#include "Cameras.h"
#include "colors.h"
#include "Models.h"

/*
Main ray tracing render loop: determine color for each pixel
*/ 
int main(int argc, char *argv[]){
    //usage: <executable> rendering_alg=[whitted, distributed, monte carlo (bidirectional), mlt, photon mapping] width sample_count, scene
    //./a.out whitted pfm 512 100 scene //(scene contains objects and camera?)
    if (argc < 2) {
        std::perror("Invalid Argument. Usage is: [executable_name] [img-out-path]");
        exit(EXIT_FAILURE);
    }
    
    // Set up scene with camera object, light direction, and geometric objects
    Scene scene_objects;
    PerspectiveCamera camera(480,480);
    Collision hit; // hit object to feed to Scene.rayIntersect to see if ray(i,j) intersects the scene at all
    vec3<double> light(0,-1,-1); light = unitVector(light);
    vec3<float> color;
    vec3<double> rb_center(0,1,-5);
    Sphere rb(rb_center, 1.0);
    std::shared_ptr<Sphere> sphere_ptr = std::make_shared<Sphere>(rb);
    scene_objects.add(sphere_ptr);
    int32_t hit_status = -1;
    
    // render_image is owner of unique_ptr<> which holds the array of 
    // floating point data representing the rgb pixel values
    PFMImage render_image(480, 480, 1.0, true); // (width, height, max intensity float, rgb?) -- 480x480 RGB image

    // hardcoded image dimensions of 480x480 (1:1 aspect)
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    for (uint32_t i=0;i<480;i++) { // numbered 0 to height from bottom to top
        for (uint32_t j=0;j<480;j++) { // numbered 0 to width from left to right
            color = black;
            Ray ray = camera.pixelToRay(i,j);
            hit_status = scene_objects.rayIntersect(&hit, ray);
            //std::cout << (hit_status) << std::endl;
            if (hit_status<0) color = black;
            else {
                float diffuse = 1.0;//std::max(0.0,dot(hit.surface_normal, -light));
                color = (diffuse*white);
            }
            (*(render_image.img_array.get()))[i][j] = color; 
        }
    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Render complete. Elapsed time: " ;
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[μs]" << std::endl;

    if (render_image.writePFM(argv[1])<0) {
        std::perror("Writing image failed. Exiting.");
        exit(EXIT_FAILURE);
    }
    std::cout << "Done writing image.\n";
    return 0; // EXIT_SUCCESS;  
}