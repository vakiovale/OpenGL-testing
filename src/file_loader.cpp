#include "file_loader.h"

std::string FileLoader::load(std::string file) {
    std::ifstream file_stream(file);
    std::string content((std::istreambuf_iterator<char>(file_stream)),
                        std::istreambuf_iterator<char>());
    return content;
}
