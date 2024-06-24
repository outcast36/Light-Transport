#include <stdexcept>
#include <cstdio>
#include "FileHandle.h"

FileHandle::FileHandle(const char * file_name, const char * mode){
    f = fopen(file_name, mode);
    if (!f) throw std::runtime_error("Failed to open file");
}

FileHandle::~FileHandle(){
    fclose(f);
}

size_t FileHandle::readFile(char * buffer, size_t size)
{
    size_t read_count = fread(buffer, 1, size, f);
    // ferror returns a nonzero value if the given file stream has any errors
    if ((read_count != size) && ferror(f)) throw std::runtime_error("Failed to read from file");
    return read_count;
}

void FileHandle::writeFile(const char * buffer, size_t size)
{
    size_t write_count = fwrite(buffer, 1, size, f);
    if (write_count != size) throw std::runtime_error("Failed to write to file");
}

bool FileHandle::is_eof(){
    return feof(f);
}