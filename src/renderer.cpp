#include "renderer.h"

void Renderer::createVertexShader(GLuint program) {
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char* vertexShaderSource =
        "#version 450 core\n"
        "layout (location = 0) in vec4 vPosition;"
        "void main()"
        "{"
        "gl_Position = vPosition;"
        "}";
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    glAttachShader(program, vertexShader);
}

void Renderer::createFragmentShader(GLuint program) {
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragmentShaderSource =
        "#version 450 core\n"
        "layout (location = 0) out vec4 fColor;"
        "void main()"
        "{"
        "fColor = vec4(0.5, 0.4, 0.8, 1.0);"
        "}";
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glAttachShader(program, fragmentShader);
}

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

    createVertexShader(program);
    createFragmentShader(program);

    glLinkProgram(program);
    glUseProgram(program);

    glBindVertexArray(vertexArrayObjects[FIRST_VERTEX_ARRAY]);
    glBindBuffer(GL_ARRAY_BUFFER, buffers[FIRST_BUFFER_OBJECT]);
    glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, NULL);
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
