#include <cstdint>
#include <iostream>
#include "FileHandle.h"

int main(int argc, char *argv[]){
    FileHandle img("../test_images/memorial.pfm", "r");
    return 0;
}