#include "renderer.h"

static std::array<GLfloat, 9> object = {-0.3, -0.3, 0.0, 0.0, -0.3, 0.0, -0.3, 0.0, 0.0};

static std::array<GLfloat, 9> colors = {1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0};

Renderer::Renderer(GLFWwindow* window) : window(*window) {}

void Renderer::createProgram() {
    GLuint program = glCreateProgram();

    createVertexShader(program);
    createFragmentShader(program);

    glLinkProgram(program);
    glUseProgram(program);
}

void Renderer::createShader(GLuint program, std::string file, GLenum shaderType) {
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

glm::mat4 Renderer::selectCameraLens(float fieldOfView) const {
    return glm::perspective(glm::radians(fieldOfView), (float)this->width / (float)this->height,
                            0.1f, 100.0f);
}

glm::mat4 Renderer::setupCameraPosition() const {
    glm::vec3 cameraPosition = glm::vec3(4, 3, 20);
    glm::vec3 cameraLookAt = glm::vec3();
    glm::vec3 cameraRotation = glm::vec3(0, 1, 0);
    return glm::lookAt(cameraPosition, cameraLookAt, cameraRotation);
}

glm::mat4 Renderer::setupModel() const {
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(glm::vec3(7.0f, 5.0f, 0.0f));
    glm::mat4 scale = glm::scale(glm::vec3(30.0f));
    glm::mat4 rotate = glm::rotate(glm::quarter_pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
    return translate * scale * rotate * model;
}

glm::mat4 Renderer::createMVP() const {
    glm::mat4 projection = selectCameraLens(45.0f);
    glm::mat4 view = setupCameraPosition();
    glm::mat4 model = setupModel();
    glm::mat4 mvp = projection * view * model;
    return mvp;
}

void Renderer::initialize() {
    spdlog::info("Initializing OpenGL");

    enableDebug();

    glfwGetWindowSize(&window, &width, &height);

    createProgram();

    glCreateVertexArrays(NUMBER_OF_VERTEX_ARRAY, vertexArrayObjects);
    glCreateBuffers(NUMBER_OF_BUFFER_OBJECTS, buffers);

    glNamedBufferStorage(buffers[FIRST_BUFFER_OBJECT], (sizeof(object) + sizeof(colors)) * 2,
                         nullptr, GL_DYNAMIC_STORAGE_BIT);
    glNamedBufferSubData(buffers[FIRST_BUFFER_OBJECT], 0, sizeof(object), object.data());
    glNamedBufferSubData(buffers[FIRST_BUFFER_OBJECT], sizeof(object), sizeof(colors),
                         colors.data());

    glBindVertexArray(vertexArrayObjects[FIRST_VERTEX_ARRAY]);
    glBindBuffer(GL_ARRAY_BUFFER, buffers[FIRST_BUFFER_OBJECT]);

    glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glVertexAttribPointer(vColor, 3, GL_FLOAT, GL_FALSE, 0, (void*)sizeof(object));
    glEnableVertexAttribArray(vPosition);
    glEnableVertexAttribArray(vColor);
}

void Renderer::render() {
    const GLfloat color[] = {0.0f, 0.0f, 0.0f, 1.0f};
    glClearBufferfv(GL_COLOR, 0, color);
    draw();
}

void Renderer::draw() {
    glBindVertexArray(vertexArrayObjects[FIRST_VERTEX_ARRAY]);
    glm::mat4 mvp = createMVP();
    glUniformMatrix4fv(2, 1, GL_FALSE, glm::value_ptr(mvp));
    glDrawArrays(GL_TRIANGLES, 0, object.size() / 3);
}
