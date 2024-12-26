#include <iostream>
#include <cstdlib>
#include <cmath>
#include <chrono>
#include "FileHandle.h"
#include "PFMImageIO.h"
#include "vec3.h"
#include "Geometry.h"
#include "Cameras.h"

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

    vec3<float> red(1,0,0);
    vec3<float> white(1,1,1);
    vec3<double> c(0,0,-5);
    PerspectiveCamera camera(640,480);
    Collision hit;
    Sphere red_ball;
    red_ball.center = c;
    red_ball.radius = 1.0;

    // render_image is owner of unique_ptr<> which holds the array of 
    // floating point data representing the rgb pixel values
    PFMImage render_image(640, 480, 1.0, true); // 640x480 RGB image

    // hardcoded image dimensions of 640x480 (4:3 aspect)
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    for (uint32_t i=0;i<480;i++) { // numbered 0 to height from bottom to top
        for (uint32_t j=0;j<640;j++) { // numbered 0 to width from left to right
            Ray ray = camera.pixelToRay(i,j);
            if (rayIntersect(&hit,ray,red_ball)==0) (*(render_image.img_array.get()))[i][j] = red;
            else (*(render_image.img_array.get()))[i][j] = white;  
        }
    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Render complete. Elapsed time: " ;
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[μs]" << std::endl;

    if (render_image.writePFM(argv[1])<0) {
        std::perror("Writing image failed. Exiting.");
        exit(EXIT_FAILURE);
    }
    std::cout << "Done writing image\n";
    return 0; // EXIT_SUCCESS;  
}