#include <string>
#include <cstdio>

class FileHandle {
    public:
        FileHandle(const char * file_name, const char * mode);
        ~FileHandle();

        // Delete these two so destructor doesn't try to release the same resource twice
        // https://bajamircea.github.io/coding/cpp/2015/03/17/classic-raii.html
        FileHandle(const FileHandle &) = delete; //copy constructor
        FileHandle & operator=(const FileHandle &) = delete; //assignment operator
        
        size_t readFile(char * buffer, size_t size);
        void writeFile(const char * buffer, size_t size);
        bool is_eof();
    private: 
        FILE *f;
};