#ifndef PFMIMAGEIO_H
#define PFMIMAGEIO_H

#include <memory>
#include <vector>
#include "FileHandle.h"
#include "vec3.h"

using rgb32 = vec3<float>;
using pixelMap = std::vector<std::vector<rgb32>>; // switch to std::array

class PFMImage {
 public:
  std::unique_ptr<pixelMap> img_array;
  PFMImage(uint32_t img_width, uint32_t img_height, float pixel_max, bool RGB);
  int32_t readPFM(std::string infile);    
  int32_t writePFM(std::string outfile);

 private:
  uint32_t img_width;
  uint32_t img_height;
  float pixel_max;
  bool RGB; // true if image is tri-channel
  int32_t readPFMHeader(FileHandle& fh);
  int32_t writePFMHeader(FileHandle& fh);
};

#endif /* PFMIMAGEIO_H */