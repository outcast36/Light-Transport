#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <chrono>
#include "FileHandle.h"
#include "PFMImageIO.h"
#include "vec3.h"
#include "Shapes.h"
#include "Geometry.h"
#include "Cameras.h"
#include "colors.h"
#include "Models.h"

// currently without an acceleration structure -- linear search through objects 
int32_t closestIntersect(std::vector<Model>& objects, Collision* closest_hit, Ray ray) {
    Collision cur;
    int32_t res=-1; // return -1 on no intersection
    for (uint32_t i=0;i<objects.size();i++) {
        if (objects[i].geometry.rayIntersect(&cur, ray)==0) {
            res=0;
            if (i==0) *closest_hit = cur;
            if (cur.t < closest_hit->t) *closest_hit = cur;
        }
    }
    return res;
}

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

    std::vector<Model> scene_objects;
    
    vec3<double> c(0,0,-5);
    vec3<double> point_in_plane(0,0,0);
    vec3<double> j_hat(0,1,0);
    vec3<float> color(0,0,0);
    vec3<double> light(0,-1,-1);
    light = unitVector(light);
    
    PerspectiveCamera camera(480,480);
    Collision hit;
    Sphere ball_geom;
    ball_geom.center = c;
    ball_geom.radius = 1.0;
    Model ball(red, ball_geom);

    Plane floor;
    floor.normal = j_hat;
    floor.point = point_in_plane;
    Model fp(lime, floor);
    
    int32_t hit_status;
    scene_objects.push_back(ball);
    scene_objects.push_back(fp);

    // render_image is owner of unique_ptr<> which holds the array of 
    // floating point data representing the rgb pixel values
    PFMImage render_image(480, 480, 1.0, true); // 640x480 RGB image

    // hardcoded image dimensions of 640x480 (4:3 aspect)
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    for (uint32_t i=0;i<480;i++) { // numbered 0 to height from bottom to top
        for (uint32_t j=0;j<480;j++) { // numbered 0 to width from left to right
            Ray ray = camera.pixelToRay(i,j);
            hit_status = closestIntersect(scene_objects, &hit, ray);
            if (hit_status<0) color = black;
            else {
                float diffuse = std::max(0.0,dot(hit.surface_normal, -light));
                color = (diffuse*red);
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
    std::cout << "Done writing image\n";
    return 0; // EXIT_SUCCESS;  
}