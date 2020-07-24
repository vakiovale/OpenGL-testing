#include "input_handler.h"

InputHandler::InputHandler() {
    last_x_pos_ = 0;
    last_y_pos_ = 0;
}

void InputHandler::setCamera(Camera& camera) { camera_ = &camera; }

Camera* InputHandler::getCamera() {
    return camera_;
}

void InputHandler::setCursorPosition(double pos_x, double pos_y) {
    last_x_pos_ = pos_x;
    last_y_pos_ = pos_y;
}

void InputHandler::translate(glm::vec3 translate) { camera_->position += translate; }

double InputHandler::getLastXPosition() const { return last_x_pos_; }

double InputHandler::getLastYPosition() const { return last_y_pos_; }
