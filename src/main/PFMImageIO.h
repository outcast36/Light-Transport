#ifndef PFMIMAGEIO_H
#define PFMIMAGEIO_H

#include <memory>
#include <vector>
#include "FileHandle.h"
#include "vec3.h"

using rgb32 = vec3<float>;
using pixelMap = std::vector<std::vector<rgb32>>;

class PFMImage {
    private:
        std::unique_ptr<pixelMap> img_array; // <- woag free memory management
        uint32_t img_width;
        uint32_t img_height;
        float pixel_max;
        bool RGB; // true if image is tri-channel
        int32_t readPFMHeader(FileHandle& fh);
        int32_t writePFMHeader(FileHandle& fh);
    public:
        PFMImage(uint32_t img_width, uint32_t img_height, float pixel_max, bool RGB);
        int32_t readPFM(PFMImage* img,  std::string infile);    
        int32_t writePFM(PFMImage* img,  std::string outfile);
        void writePixel(uint32_t i, uint32_t j);
};

#endif /* PFMIMAGEIO_H */