#include <iostream>
#include <cstdlib>
#include "FileHandle.h"
#include "PFMImageIO.h"
#include "vec3.h"

int main(int argc, char *argv[]){
    //usage: <executable> rendering_alg=[whitted, distributed, monte carlo (bidirectional), mlt, photon mapping] width sample_count, scene
    //./a.out whitted pfm 512 100 scene //(scene contains objects and camera?)
    if (argc < 2) {
        std::perror("Invalid Argument. Usage is: ./a.out [img-path]");
        exit(EXIT_FAILURE);
    }
    // in_image is owner of unique_ptr<> which holds the array of 
    // floating point data representing the rgb pixel values
    PFMImage in_image; 
    if (readPFM(&in_image, argv[1]) < 0) {
        std::perror("Reading image failed. Exiting.");
        exit(EXIT_FAILURE);
    }
    std::cout << "Done reading image\n";
    if (writePFM(&in_image, "write_test.pfm")<0) {
        std::perror("Writing image failed. Exiting.");
        exit(EXIT_FAILURE);
    }
    std::cout << "Done writing image\n";
    return 0; // EXIT_SUCCESS;
}