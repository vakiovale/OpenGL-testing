#ifndef RENDERER_H_
#define RENDERER_H_

#include <glad/glad.h>
#include <spdlog/spdlog.h>

#include <glm/common.hpp>

#include "file_loader.h"
#include "glfw.h"
#include "message_callback.h"

class Renderer {
   private:
    enum VAO_ID { FIRST_VERTEX_ARRAY, NUMBER_OF_VERTEX_ARRAY };
    enum BUFFER_ID { FIRST_BUFFER_OBJECT, NUMBER_OF_BUFFER_OBJECTS };
    enum ATTRIBUTE_ID { vPosition = 0, vColor = 1 };

    void createShader(GLuint program, std::string file, GLenum shaderType);
    void createVertexShader(GLuint program);
    void createFragmentShader(GLuint program);
    GLuint vertexArrayObjects[NUMBER_OF_VERTEX_ARRAY];
    GLuint buffers[NUMBER_OF_BUFFER_OBJECTS];
    const FileLoader fileLoader;

   public:
    void initialize();
    void render();
    void createProgram();
};

#endif
