#include "FileHandle.h"

struct PFMImage{
    uint32_t img_width;
    uint32_t img_height;
    bool RGB; // false if image is greyscale (1 channel), true if image is RGB (3 channels)
    vector<vector<PixelRGB>> 
};

//readPFM()

//writePFM()

bool isWhiteSpace(char c){
    return c==' ' || c=='\t' || c=='\r' || c=='\n' || c=='\v' || c=='\f';
}

//readWord()