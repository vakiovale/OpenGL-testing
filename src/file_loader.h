#ifndef FILE_LOADER_H_
#define FILE_LOADER_H_

#include <fstream>
#include <streambuf>
#include <string>

class FileLoader {
   public:
    std::string load(std::string file);
};

#endif
