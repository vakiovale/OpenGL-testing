#ifndef OBJECT_RESOURCE_H_
#define OBJECT_RESOURCE_H_

#include <glm/glm.hpp>

#include "object_loader.h"

typedef struct {
    std::string file;
    object object;
    glm::vec3 translate;
} object_resource;

#endif
