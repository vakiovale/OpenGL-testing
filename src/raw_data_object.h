#ifndef RAW_DATA_OBJECT_H_
#define RAW_DATA_OBJECT_H_

#include <glad/glad.h>
#include <vector>

typedef struct {
    std::vector<GLfloat> vertices;
    std::vector<GLfloat> colors;
} raw_data_object;

#endif
