#include "renderer.h"

static std::array<GLfloat, 9> object = {-0.3, -0.3, 0.0, 0.0, -0.3,
                                        0.0,  -0.3, 0.0, 0.0};

static std::array<GLfloat, 9> colors = {1.0, 0.0, 0.0, 0.0, 1.0,
                                        0.0, 0.0, 0.0, 1.0};

void Renderer::createProgram() {
    GLuint program = glCreateProgram();

    createVertexShader(program);
    createFragmentShader(program);

    glLinkProgram(program);
    glUseProgram(program);
}

void Renderer::createShader(GLuint program, std::string file,
                            GLenum shaderType) {
    GLuint shader = glCreateShader(shaderType);
    const std::string shaderSource = fileLoader.load("resources/glsl/" + file);
    const GLchar* source = shaderSource.c_str();
    spdlog::info("Loaded shader:\n" + shaderSource);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
    glAttachShader(program, shader);
}

void Renderer::createVertexShader(GLuint program) {
    createShader(program, "vertex_shader.glsl", GL_VERTEX_SHADER);
}

void Renderer::createFragmentShader(GLuint program) {
    createShader(program, "fragment_shader.glsl", GL_FRAGMENT_SHADER);
}

void Renderer::initialize() {
    spdlog::info("Initializing OpenGL");

    enableDebug();

    createProgram();

    glCreateVertexArrays(NUMBER_OF_VERTEX_ARRAY, vertexArrayObjects);
    glCreateBuffers(NUMBER_OF_BUFFER_OBJECTS, buffers);

    glNamedBufferStorage(buffers[FIRST_BUFFER_OBJECT],
                         (sizeof(object) + sizeof(colors)) * 2, nullptr,
                         GL_DYNAMIC_STORAGE_BIT);
    glNamedBufferSubData(buffers[FIRST_BUFFER_OBJECT], 0, sizeof(object),
                         object.data());
    glNamedBufferSubData(buffers[FIRST_BUFFER_OBJECT], sizeof(object),
                         sizeof(colors), colors.data());

    glBindVertexArray(vertexArrayObjects[FIRST_VERTEX_ARRAY]);
    glBindBuffer(GL_ARRAY_BUFFER, buffers[FIRST_BUFFER_OBJECT]);

    glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glVertexAttribPointer(vColor, 3, GL_FLOAT, GL_FALSE, 0,
                          (void*)sizeof(object));
    glEnableVertexAttribArray(vPosition);
    glEnableVertexAttribArray(vColor);

}

void Renderer::render() {
    const float redValue = sin(glfwGetTime()) * 0.5f + 0.5f;
    const float greenValue = cos(glfwGetTime() + M_PI / 2) * 0.5f + 0.5f;
    const GLfloat red[] = {redValue, greenValue, 0.0f, 1.0f};
    glClearBufferfv(GL_COLOR, 0, red);
    glBindVertexArray(vertexArrayObjects[FIRST_VERTEX_ARRAY]);
    glDrawArrays(GL_TRIANGLES, 0, object.size() / 3);
}
