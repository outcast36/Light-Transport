#ifndef FILEHANDLE_H
#define FILEHANDLE_H

#include <cstddef>
#include <cstdio>

class FileHandle {
 public:
  FileHandle(const char * file_name, const char * mode);
  ~FileHandle();
  // Delete these two so destructor doesn't try to release the same resource twice
  // https://bajamircea.github.io/coding/cpp/2015/03/17/classic-raii.html
  FileHandle(const FileHandle &) = delete; //copy constructor
  FileHandle& operator=(const FileHandle &) = delete; //assignment operator   
  int32_t readFile(void* buffer, size_t size, size_t count);
  int32_t readLine(char* buffer);
  int32_t writeFile(const void* buffer, size_t size, size_t count);
  bool is_eof();

 private: 
  FILE *f;
};

#endif /* FILEHANDLE_H */