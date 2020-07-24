#ifndef CAMERA_H_
#define CAMERA_H_

#include <glm/glm.hpp>

typedef struct {
    glm::vec3 position = glm::vec3(4, 3, 20);
    glm::vec3 look_at = glm::vec3();
    glm::vec3 rotation = glm::vec3(0, 1, 0);
    float pitch = 0.0;
    float yaw = 0.0;
    float roll = 0.0;
    glm::quat orientation = glm::quat();
} Camera;

#endif
