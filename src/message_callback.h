#include <glad/glad.h>
#include <spdlog/spdlog.h>

#include <string>

static void messageCallback(GLenum source, GLenum type, GLuint id,
                            GLenum severity, GLsizei length,
                            const GLchar* message, const void* userParam);

void enableDebug();
