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
    pixelMap* img_array;
    uint32_t img_width;
    uint32_t img_height;
    float pixel_max;
    bool RGB; // true if image is tri-channel
};

using PFMImage = struct PFMImage;

int32_t readPFMHeader(FileHandle& fh, PFMImage* img) {
    char buf[128]={0}; // char buffer for header 
    uint32_t width=0, height=0;
    float pixel_max=-1.0F;
    bool color=false; 
    const char* delim=" ";

    // Line 1: One of "PF" (tri-channel color) or "Pf" (monochrome single-channel) 
    int32_t n = fh.readLine(&buf[0]);
    if (n<0) return -1;
    color = (buf[1]=='F'); 
    // Line 2: [xres] [yres]
    n = fh.readLine(&buf[0]);
    if (n<0) return -1;
    char* tok  = strtok(&buf[0], delim); 
    width = std::stoi(tok);
    tok = strtok(NULL, delim);
    height = std::stoi(tok);
    // Line 3: scale factor and endianess
    n = fh.readLine(&buf[0]);
    if (n<0) return -1;
    pixel_max = std::stof(buf);
    img->img_width = width;
    img->img_height = height;
    img->pixel_max = std::abs(pixel_max);
    img->RGB = color;
    return 0;
}

PFMImage* readPFM(PFMImage* img,  std::string infile) {
    uint32_t width, height;
    int32_t n;
    float pixel[3]; // RGB channel value buffer
    FileHandle fh = FileHandle(infile.c_str(), "r");
    n=readPFMHeader(fh,img);
    if(n<0) return NULL;
    width = img->img_width; height = img->img_height;
    std::cout << "Color: " << img->RGB << " Width: " << width << " Height: ";
    std::cout << height << " Max Pixel Value: " << img->pixel_max << '\n';
    pixelMap pixels(width, std::vector<vec3<float>>(height));
    for (uint32_t i=0;i<width;i++) { // numbered 0 to width from left to right
        for (uint32_t j=0;j<height;j++) { // numbered 0 to height from bottom to top
            n=fh.readFile(&pixel[0], 3*sizeof(float), 1); // read 12 bytes into float[3]
            if (n<0) return NULL;
            pixels[i][j]=vec3<float>(pixel[0], pixel[1], pixel[2]);
        }
    }
    img->img_array = &pixels;
    return img; // destructor of FileHandle instance invoked on return 
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
    PFMImage inImage;
    if (readPFM(&inImage, argv[1]) == NULL) {
        std::perror("Image IO failed. Exiting.");
        exit(EXIT_FAILURE);
    }
    return 0; // EXIT_SUCCESS;
}