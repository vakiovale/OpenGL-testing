#ifndef OBJECT_LOADER_H_
#define OBJECT_LOADER_H_

#include <glad/glad.h>
#include <tiny_obj_loader.h>

#include <string>

typedef struct {
    std::vector<GLfloat> vertices;
    std::vector<GLfloat> colors;
} object;

object loadObject(std::string file);

#endif
