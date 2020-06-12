#ifndef RENDERER_H_
#define RENDERER_H_

#include <glad/glad.h>
#include <spdlog/spdlog.h>

#include <glm/ext/scalar_constants.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

#include "file_loader.h"
#include "glfw.h"
#include "message_callback.h"
#include "object_loader.h"

class Renderer {
   private:
    enum VAO_ID { FIRST_VERTEX_ARRAY, NUMBER_OF_VERTEX_ARRAY };
    enum BUFFER_ID { FIRST_BUFFER_OBJECT, NUMBER_OF_BUFFER_OBJECTS };
    enum ATTRIBUTE_ID { vPosition = 0, vColor = 1 };

    void createShader(GLuint program, std::string file, GLenum shaderType);
    void createVertexShader(GLuint program);
    void createFragmentShader(GLuint program);
    glm::mat4 setupCameraPosition() const;
    glm::mat4 selectCameraLens(float fieldOfView) const;
    glm::mat4 setupModel() const;
    glm::mat4 createMVP() const;
    void draw();

    int width;
    int height;
    GLuint vertexArrayObjects[NUMBER_OF_VERTEX_ARRAY];
    GLuint buffers[NUMBER_OF_BUFFER_OBJECTS];
    const FileLoader fileLoader;
    GLFWwindow &window;

   public:
    Renderer(GLFWwindow *window);
    void initialize();
    void render();
    void createProgram();
};

#endif
