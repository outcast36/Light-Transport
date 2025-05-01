#include <string>
#include <vector>
#include <cstdio>
#include <memory>
#include <string.h>
#include "PFMImageIO.h"

PFMImage::PFMImage(uint32_t img_width, uint32_t img_height, float pixel_max, bool RGB) 
    : img_width(img_width),
      img_height(img_height),
      pixel_max(pixel_max),
      RGB(RGB) {
    pixelMap pixels(img_height, std::vector<rgb32>(img_width));
    this->img_array = std::make_unique<pixelMap>(pixels);
}

/* 
This function exists as a helper function, to be called only within writePFM().
Assuming well-formed data, img has a bunch of floating point data, the 
dimensions of the image, whether or not the image is rgb, the endianess of the data, 
and the maximum floating point value used to represent full saturation of R, G, or B. 
Also assume that fh is a valid FileHandle and can be written to. 
*/
int32_t PFMImage::writePFMHeader(FileHandle& fh) {
    const uint8_t buf_size = 128;
    char buf[buf_size]={0}; // char buffer for header 
    int32_t n, digits_w, digits_h;
    // Line 1: One of "PF" (tri-channel color) or "Pf" (monochrome single-channel)
    if (this->RGB) strcpy(buf, "PF\n");
    else strcpy(buf,"Pf\n");
    n = fh.writeFile(&buf[0],sizeof(char),strlen(buf));
    if (n<0) return -1;
    // Line 2: [xres] [yres]
    memset(buf,'\0',buf_size);
    digits_w = snprintf(NULL,0,"%u",this->img_width);
    snprintf(&buf[0],digits_w+1,"%u",this->img_width);
    digits_h = snprintf(NULL,0,"%u",this->img_height);
    buf[digits_w]=' ';
    snprintf(&buf[digits_w+1],digits_h+1,"%u",this->img_height);
    n=strlen(buf); buf[n]='\n';
    n = fh.writeFile(&buf[0],sizeof(char),n+1);
    if (n<0) return -1;
    // Line 3: scale factor and endianess
    memset(buf,'\0',buf_size);
    buf[0]='-';
    digits_w = snprintf(NULL,0,"%f",this->pixel_max);
    snprintf(&buf[1],digits_w+1,"%f",this->pixel_max);
    n=strlen(buf); buf[n]='\n';
    n = fh.writeFile(&buf[0],sizeof(char),n+1);
    if (n<0) return -1;
    return 0;
}

/* 
This function exists as a helper function, to be called only within readPFM().
Assuming well-formed data, img has a bunch of floating point data, the 
dimensions of the image, whether or not the image is rgb, the endianess of the data, 
and the maximum floating point value used to represent full saturation of R, G, or B. 
Also assume that fh is a valid FileHandle and can be read from. 
*/
int32_t PFMImage::readPFMHeader(FileHandle& fh) {
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
    this->img_width = width;
    this->img_height = height;
    this->pixel_max = std::abs(pixel_max);
    this->RGB = color;
    return 0;
}

// Read a PFM image in its entirety from the given path: infile.pfm
// Data is output into the pointer img
int32_t PFMImage::readPFM(std::string infile) {
    uint32_t width, height;
    int32_t n;
    float pixel[3]; // RGB channel value buffer
    FileHandle fh(infile.c_str(), "r");
    n=readPFMHeader(fh);
    if(n<0) return -1;
    width = this->img_width; height = this->img_height;
    pixelMap pixels(height, std::vector<rgb32>(width));
    for (uint32_t i=0;i<height;i++) { // numbered 0 to height from bottom to top
        for (uint32_t j=0;j<width;j++) { // numbered 0 to width from left to right
            n=fh.readFile(&pixel[0], 3*sizeof(float), 1); // read 12 bytes into float[3]
            if (n<0) return -1;
            pixels[i][j]=vec3<float>(pixel[0], pixel[1], pixel[2]);
        }
    }
    this->img_array = std::make_unique<pixelMap>(pixels);
    return 0; // destructor of FileHandle instance invoked on return 
}

// Write all of the PFM image data from the pointer img into the file: outfile.pfm
int32_t PFMImage::writePFM(std::string outfile) {
    uint32_t width=this->img_width, height=this->img_height;
    int32_t n;
    FileHandle fh(outfile.c_str(), "w");
    pixelMap pixels = *(this->img_array.get());
    n=writePFMHeader(fh);
    if(n<0) return -1;
    for (uint32_t i=0;i<height;i++) { // numbered 0 to height from bottom to top
        for (uint32_t j=0;j<width;j++) { // numbered 0 to width from left to right
            n=fh.writeFile(&pixels[i][j], 3*sizeof(float), 1);
            if (n<0) return -1;
        }
    }
    return 0; // destructor of FileHandle instance invoked on return 
}