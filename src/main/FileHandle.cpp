#include "FileHandle.h"

FileHandle::FileHandle(const char * file_name, const char * mode){
    f = fopen(file_name, mode);
    if (!f) std::perror("Failed to open file");
}

FileHandle::~FileHandle(){
    fclose(f);
}

size_t FileHandle::readFile(char* buffer, size_t size, size_t count) {
    size_t read_count = fread(buffer, size, count, f); // read given size parameter bytes
    // ferror returns a nonzero value if the given file stream has any errors
    // fread returns count of objects read successfully
    if ((read_count != count) && ferror(f)) std::perror("Failed to read from file");
    else if (read_count != count && this->is_eof()) std::perror("Read to EOF successfully");
    return read_count;
}

void FileHandle::writeFile(const char* buffer, size_t size, size_t count)
{
    size_t write_count = fwrite(buffer, size, count, f);
    if (write_count != count && ferror(f)) std::perror("Failed to write to file");
}

bool FileHandle::is_eof(){
    return feof(f);
}