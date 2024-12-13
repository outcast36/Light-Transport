#include <iostream>
#include <string>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <bit>
#include "FileHandle.h"
#include "vec3.h"

using pixelMap = std::vector<std::vector<vec3<float>>>;

struct PFMImage {
    uint32_t img_width;
    uint32_t img_height;
    float pixel_max;
    bool RGB; // true if image is tri-channel
    pixelMap img_array;
};

using PFMIMage = struct PFMImage;

PFMImage* readPFM(const std::string infile) {
    char buf[128]={0}; // char buffer for header 
    //float pixel[3]; // RGB channel value buffer
    uint32_t width=0, height=0;
    float pixel_max=-1.0F;
    bool color=false; 
    const char* delim=" ";

        FileHandle fh = FileHandle(infile.c_str(), "r");
        // Line 1: One of "PF" (tri-channel color) or "Pf" (monochrome single-channel) 
        int32_t n = fh.readLine(&buf[0]);
        if (n<0) return NULL;
        color = (buf[1]=='F'); 
        // Line 2: [xres] [yres]
        n = fh.readLine(&buf[0]);
        if (n<0) return NULL;
        char* tok  = strtok(&buf[0], delim); 
        width = std::stoi(tok);
        tok = strtok(NULL, delim);
        height = std::stoi(tok);
        // Line 3: scale factor and endianess
        n = fh.readLine(&buf[0]);
        if (n<0) return NULL;
        pixel_max = std::stof(buf);
        std::cout << "Color: " << color << " Width: " << width << " Height: ";
        std::cout << height << " Max Pixel Value: " << pixel_max << '\n';
        //pixelMap pixels(width, std::vector<vec3<float>>(height));
        //for (int i=0;i<width;i++) { // numbered 0 to width from left to right
        //    for (int j=0;j<height;j++) { // numbered 0 to height from bottom to top
        //        for (int k=0;k<3;k++) {
        //            n = fh.readFile(&buf[0], 1, 4);
        //            std::printf("%x\n", buf[1]);
        //            if (n<0) throw new std::runtime_error("Failed to read line from file.");
        //        }
        //        pixels[i][j]=vec3(pixel[0], pixel[1], pixel[2]);
        //    }
        //}
    // malloc PFMImage struct to access it outisde of here
    return NULL; // destructor of FileHandle instance invoked on return 
}

bool isWhiteSpace(char c){
    return c==' ' || c=='\t' || c=='\r' || c=='\n' || c=='\v' || c=='\f';
}

int main(int argc, char *argv[]){
    //usage: <executable> rendering_alg=[whitted, distributed, monte carlo (bidirectional), mlt, photon mapping] width sample_count, scene
    //./a.out whitted pfm 512 100 scene //(scene contains objects and camera?)
    if (argc < 2) {
        std::perror("Invalid Argument. Usage is: ./a.out [img-path]");
        exit(EXIT_FAILURE);
    }
    //PFMImage* inImage = readPFM(argv[1]);
    readPFM(argv[1]);
    //if (inImage == NULL) {
    //    std::perror("Image IO failed. Exiting.");
    //    exit(EXIT_FAILURE);
    //}
    return 0; // EXIT_SUCCESS;
}