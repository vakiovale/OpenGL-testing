#include "renderer.h"

#include <numeric>

void Renderer::initialize() {
    spdlog::info("Initializing OpenGL");

    const GLfloat vertices[6][2] = {{-0.90, -0.90}, {0.85, -0.90},
                                    {-0.90, 0.85},  {0.90, -0.85},
                                    {0.90, 0.90},   {-0.85, 0.90}};

    glCreateVertexArrays(NUMBER_OF_VERTEX_ARRAY, vertexArrayObjects);
    glCreateBuffers(NUMBER_OF_BUFFER_OBJECTS, buffers);

    glNamedBufferStorage(buffers[FIRST_BUFFER_OBJECT], sizeof(vertices),
                         vertices, 0);
    GLuint program = glCreateProgram();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char* vertexShaderSource =
        "#version 450 core\n"
        "layout (location = 0) in vec4 vPosition;\n"
        "void main()\n"
        "{\n"
        "gl_Position = vPosition;\n"
        "}";
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    glAttachShader(program, vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragmentShaderSource =
        "#version 450 core\n"
        "layout (location = 0) out vec4 fColor;\n"
        "void main()\n"
        "{\n"
        "fColor = vec4(0.5, 0.4, 0.8, 1.0);\n"
        "}";
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glAttachShader(program, fragmentShader);

    glLinkProgram(program);
    glUseProgram(program);

    glBindVertexArray(vertexArrayObjects[FIRST_VERTEX_ARRAY]);
    glBindBuffer(GL_ARRAY_BUFFER, buffers[FIRST_BUFFER_OBJECT]);
    glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, ((char *)NULL + 0));
    glEnableVertexAttribArray(vPosition);
}

void Renderer::render() {
    const float redValue = sin(glfwGetTime()) * 0.5f + 0.5f;
    const float greenValue = cos(glfwGetTime() + M_PI / 2) * 0.5f + 0.5f;
    const GLfloat red[] = {redValue, greenValue, 0.0f, 1.0f};
    glClearBufferfv(GL_COLOR, 0, red);
    glBindVertexArray(vertexArrayObjects[FIRST_VERTEX_ARRAY]);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}
