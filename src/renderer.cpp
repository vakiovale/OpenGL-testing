#include "renderer.h"

void Renderer::createVertexShader(GLuint program) {
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const std::string vertexShaderSource = fileLoader.load("resources/glsl/vertex_shader.glsl");
    const GLchar* source = vertexShaderSource.c_str();
    spdlog::info("Loaded shader:\n" + vertexShaderSource);
    glShaderSource(vertexShader, 1, &source, NULL);
    glCompileShader(vertexShader);
    glAttachShader(program, vertexShader);
}

void Renderer::createFragmentShader(GLuint program) {
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const std::string fragmentShaderSource = fileLoader.load("resources/glsl/fragment_shader.glsl");
    const GLchar* source = fragmentShaderSource.c_str();
    spdlog::info("Loaded shader:\n" + fragmentShaderSource);
    glShaderSource(fragmentShader, 1, &source, NULL);
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
