#include <stdexcept>
#include "FileHandle.h"

// Acquire file on construction
FileHandle::FileHandle(const char * file_name, const char * mode) {
    f = fopen(file_name, mode);
    if (!f) throw new std::runtime_error("Failed to open file");
}

// Release file on destruction
FileHandle::~FileHandle() {
    fclose(f);
}

// Read an arbitrary number of objects which contain can arbitrary amount of bytes
size_t FileHandle::readFile(char* buffer, size_t size, size_t count) {
    size_t read_count = fread(buffer, size, count, f); // read given size parameter bytes

    // ferror returns a nonzero value if the given file stream has any errors
    // fread returns count of objects read successfully
    if ((read_count != count) && ferror(f)) {
        throw new std::runtime_error("Failed to read from file.");
    } 

    // In the EOF case, return number of bytes to callervoid
    return read_count;
}

// Read a line delimited by newline from the file
size_t FileHandle::readLine(char* buffer) {
    size_t buffer_size=4096, line_size;
    if (line_size=getline(&buffer, &buffer_size, f)<0) {
        std::perror("Failed to get line");
    }
    return line_size;
}

// Write arbitrary amount of objects which contain an arbitrary amount of bytes
size_t FileHandle::writeFile(const char* buffer, size_t size, size_t count) {
    size_t write_count = fwrite(buffer, size, count, f);
    if (write_count != count && ferror(f)) {
        throw new std::runtime_error("Failed to write to file");
    } 
    return write_count;
}

// Check file EOF status
bool FileHandle::is_eof() {
    return feof(f);
}