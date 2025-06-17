#include <iostream>
#include <cstdlib>
#include <cmath>
#include <chrono>
#include "PFMImageIO.h"
#include "BaseObject.h"
#include "GFXBase.h"
#include "Scene.h"
#include "Cameras.h"
#include "colors.h"
#include "TestScenes.h"

/*
Main ray tracing render loop: determine color for each pixel
*/ 
int main(int argc, char *argv[]){
    //usage: <executable> <rendering algorithm> width sample_count, scene
    if (argc < 2) {
        std::perror("Invalid Argument. Usage is: [executable_name] [img-out-path]");
        exit(EXIT_FAILURE);
    }    
    
    // Set up scene with camera object, light direction, and geometric objects
    Scene scene_objects = scene2();
    PerspectiveCamera camera(480,480);
    vec3<double> light(0,-1,-1); light = unitVector(light);
    
    // render_image is owner of unique_ptr<> which holds the array of 
    // floating point data representing the rgb pixel values
    PFMImage render_image(480, 480, 1.0, true); // (width, height, max intensity float, rgb?) -- 480x480 RGB image

    // hardcoded image dimensions of 480x480 (1:1 aspect)
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    for (uint32_t i=0;i<480;i++) { // numbered 0 to height from bottom to top
        for (uint32_t j=0;j<480;j++) { // numbered 0 to width from left to right
            //std::cout << "Row: " << i << " Column: " << j << '\n';
            vec3<float> color = black;
            Ray ray = camera.pixelToRay(i,j);
            auto hit_status = scene_objects.rayIntersect(ray, Interval(0.0, MAXFLOAT));
            if (hit_status) {
                Collision hit = hit_status.value();
                //std::cout << "Closest Hit Parameter: " << hit.t << '\n';
                //std::cout << "Closest Hit Surface Normal: " << hit.surface_normal.x() << " " << hit.surface_normal.y() << " " << hit.surface_normal.z() << '\n';
                vec3<float> nf(hit.surface_normal.x(), hit.surface_normal.y(), hit.surface_normal.z());
                color = 0.5F * (nf + white);
            }
            // TODO THINK ABOUT HOW TO CLEAN THIS LINE UP AND MAKE ACCESSING PIXEL DATA EASIER
            (*(render_image.img_array.get()))[i][j] = color; 
        }
    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Render complete. Elapsed time: " ;
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[μs]\n";

    if (render_image.writePFM(argv[1])<0) {
        std::perror("Writing image failed. Exiting.");
        exit(EXIT_FAILURE);
    }
    std::cout << "Done writing image." << std::endl;
    return 0; // EXIT_SUCCESS;  
}