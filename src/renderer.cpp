#include "renderer.h"

std::string inputfile = "resources/objects/golf.obj";
object loadedObject;

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
                            0.1f, 10000.0f);
}

glm::mat4 Renderer::setupCameraPosition() const {
    glm::vec3 cameraPosition = glm::vec3(4, 3, 20);
    glm::vec3 cameraLookAt = glm::vec3();
    glm::vec3 cameraRotation = glm::vec3(0, 1, 0);
    return glm::lookAt(cameraPosition, cameraLookAt, cameraRotation);
}

glm::mat4 Renderer::setupModel() const {
    glm::mat4 model = glm::mat4(1.0f);
    const float angle = glfwGetTime() * 1.0f;
    glm::mat4 newTranslate = glm::translate(glm::vec3(0.0f, sin(angle) * 10.0f, 0.0f));
    glm::mat4 scale = glm::scale(glm::vec3(10.0f));
    glm::mat4 rotate = glm::rotate(angle, glm::vec3(0.0f, 1.0f, 0.0f));
    return newTranslate * rotate * scale * model;
}

glm::mat4 Renderer::createMVP() const {
    glm::mat4 projection = selectCameraLens(120.0f);
    glm::mat4 view = setupCameraPosition();
    glm::mat4 model = setupModel();
    glm::mat4 mvp = projection * view * model;
    return mvp;
}

void Renderer::initialize() {
    spdlog::info("Initializing OpenGL");

    loadedObject = loadObject(inputfile);

    enableDebug();

    glfwGetWindowSize(&window, &width, &height);

    createProgram();

    glCreateVertexArrays(NUMBER_OF_VERTEX_ARRAY, vertexArrayObjects);
    glCreateBuffers(NUMBER_OF_BUFFER_OBJECTS, buffers);

    glNamedBufferStorage(
        buffers[FIRST_BUFFER_OBJECT],
        sizeof(GLfloat) * (loadedObject.vertices.size() + loadedObject.colors.size()), nullptr,
        GL_DYNAMIC_STORAGE_BIT);
    glNamedBufferSubData(buffers[FIRST_BUFFER_OBJECT], 0,
                         sizeof(GLfloat) * loadedObject.vertices.size(),
                         loadedObject.vertices.data());
    glNamedBufferSubData(buffers[FIRST_BUFFER_OBJECT],
                         sizeof(GLfloat) * loadedObject.vertices.size(),
                         sizeof(GLfloat) * loadedObject.colors.size(), loadedObject.colors.data());

    glBindVertexArray(vertexArrayObjects[FIRST_VERTEX_ARRAY]);
    glBindBuffer(GL_ARRAY_BUFFER, buffers[FIRST_BUFFER_OBJECT]);

    glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glVertexAttribPointer(vColor, 3, GL_FLOAT, GL_TRUE, 0,
                          (void*)(sizeof(GLfloat) * loadedObject.vertices.size()));
    glEnableVertexAttribArray(vPosition);
    glEnableVertexAttribArray(vColor);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);
}

void Renderer::render() {
    const GLfloat color[] = {0.0f, 0.0f, 0.0f, 0.0f};
    glClearBufferfv(GL_COLOR, 0, color);
    glClear(GL_DEPTH_BUFFER_BIT);
    draw();
}

void Renderer::draw() {
    glBindVertexArray(vertexArrayObjects[FIRST_VERTEX_ARRAY]);

    glm::mat4 mvp = createMVP();
    glUniformMatrix4fv(2, 1, GL_FALSE, glm::value_ptr(mvp));
    glDrawArrays(GL_TRIANGLES, 0, loadedObject.vertices.size() / 3);
}
