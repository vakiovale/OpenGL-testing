#ifndef INPUT_HANDLER_
#define INPUT_HANDLER_

#include <spdlog/spdlog.h>

#include <glm/ext/quaternion_trigonometric.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>
#include <string>

#include "GLFW/glfw3.h"
#include "camera.h"
#include "glfw.h"
#include "spdlog/common.h"

class InputHandler {
   private:
    Camera* camera_;
    double last_x_pos_;
    double last_y_pos_;

   public:
    InputHandler();
    double getLastXPosition() const;
    double getLastYPosition() const;
    Camera* getCamera();
    void setCamera(Camera& camera);
    void setCursorPosition(double pos_x, double pos_y);
    void translate(glm::vec3 translate);
};

static InputHandler INPUT_HANDLER;

static InputHandler* getInputHandler() { return &INPUT_HANDLER; };

static void CURSORCALLBACK(GLFWwindow* window, double xpos, double ypos) {
    double x_offset = (xpos - INPUT_HANDLER.getLastXPosition());
    double y_offset = (ypos - INPUT_HANDLER.getLastYPosition());
    INPUT_HANDLER.setCursorPosition(xpos, ypos);

    auto* camera = INPUT_HANDLER.getCamera();
    camera->pitch += y_offset;
    camera->yaw += x_offset;

    glm::quat q_pitch = glm::angleAxis(camera->pitch * 0.001f, glm::vec3(1, 0, 0));
    glm::quat q_yaw = glm::angleAxis(camera->yaw * 0.001f, glm::vec3(0, 1, 0));
    glm::quat orientation = glm::normalize(q_pitch * q_yaw);

    camera->orientation = orientation;
}

static void KEYCALLBACK(GLFWwindow* window, int key, int scancode, int action, int mods) {
    auto* camera = INPUT_HANDLER.getCamera();
    auto q = camera->orientation;
    glm::vec3 forward = glm::conjugate(q) * glm::vec3(0.0f, 0.0f, 1.0f);
    glm::vec3 left = glm::conjugate(q) * glm::vec3(1.0f, 0.0f, 0.0f);

    if (key == GLFW_KEY_W) {
        camera->position += glm::normalize(forward) * 0.1f;
    }
    if (key == GLFW_KEY_S) {
        camera->position -= glm::normalize(forward) * 0.1f;
    }
    if (key == GLFW_KEY_A) {
        camera->position += glm::normalize(left) * 0.1f;
    }
    if (key == GLFW_KEY_D) {
        camera->position -= glm::normalize(left) * 0.1f;
    }
}

#endif
