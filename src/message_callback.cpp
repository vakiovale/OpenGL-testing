#include "message_callback.h"

void GLAPIENTRY messageCallback(GLenum source, GLenum type, GLuint id,
                                GLenum severity, GLsizei length,
                                const GLchar* message, const void* userParam) {
    const std::string callback_message =
        "type: " + std::to_string(type) +
        ", severity: " + std::to_string(severity) + ", message: " + " " +
        std::string(message);
    if (type == GL_DEBUG_TYPE_ERROR) {
        spdlog::error(callback_message);
    } else {
        spdlog::info(callback_message);
    }
}

void enableDebug() {
    spdlog::info("Enabling Debug message callback");
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(messageCallback, 0);
}
