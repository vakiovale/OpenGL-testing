#include "renderer.h"

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
    spdlog::debug("Loaded shader:\n" + shaderSource);
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

void Renderer::createVAOsAndGenerateBuffers() {
    GLuint vaos[this->resources.size()];
    GLuint buffers[this->resources.size()];
    glCreateVertexArrays(this->resources.size(), vaos);
    glGenBuffers(this->resources.size(), buffers);

    for (std::size_t i = 0; i < this->resources.size(); i++) {
        this->vertex_array_objects.push_back(vaos[i]);
        this->vertex_buffer_objects.push_back(buffers[i]);
    }
}

void Renderer::loadAndBindObject(const object_resource& resource, const GLuint VAO,
                                 const GLuint BUFFER) {
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, BUFFER);

    glNamedBufferStorage(
        BUFFER, sizeof(GLfloat) * (resource.object.vertices.size() + resource.object.colors.size()),
        nullptr, GL_DYNAMIC_STORAGE_BIT);
    glNamedBufferSubData(BUFFER, 0, sizeof(GLfloat) * resource.object.vertices.size(),
                         resource.object.vertices.data());
    glNamedBufferSubData(BUFFER, sizeof(GLfloat) * resource.object.vertices.size(),
                         sizeof(GLfloat) * resource.object.colors.size(),
                         resource.object.colors.data());

    glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glVertexAttribPointer(vColor, 3, GL_FLOAT, GL_TRUE, 0,
                          (void*)(sizeof(GLfloat) * resource.object.vertices.size()));
    glEnableVertexAttribArray(vPosition);
    glEnableVertexAttribArray(vColor);
}

void Renderer::initialize(std::vector<object_resource> resources) {
    spdlog::info("Initializing OpenGL");
    enableDebug();

    this->resources = resources;

    glfwGetWindowSize(&window, &width, &height);

    createProgram();
    createVAOsAndGenerateBuffers();

    spdlog::info("Load and bind objects");
    for (std::size_t i = 0; i < resources.size(); i++) {
        loadAndBindObject(resources[i], this->vertex_array_objects[i],
                          this->vertex_buffer_objects[i]);
    }
    spdlog::info("Loading objects finished");

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);

    spdlog::info("Renderer initialization finished");
}

void Renderer::render() {
    const GLfloat color[] = {0.0f, 0.0f, 0.0f, 0.0f};
    glClearBufferfv(GL_COLOR, 0, color);
    glClear(GL_DEPTH_BUFFER_BIT);
    draw();
}

glm::mat4 Renderer::createModel(const object_resource& resource) const {
    const float angle = glfwGetTime() * 1.0f;
    glm::mat4 translate =
        glm::translate(glm::vec3(0.0f, sin(angle) * 10.0f, 0.0f) + resource.translate);
    glm::mat4 scale = glm::scale(glm::vec3(10.0f));
    glm::mat4 rotate = glm::rotate(angle, glm::vec3(0.0f, 1.0f, 0.0f));
    return translate * rotate * scale;
}

void Renderer::draw() {
    glm::mat4 projection = selectCameraLens(120.0f);
    glm::mat4 view = setupCameraPosition();

    for (std::size_t i = 0; i < this->resources.size(); i++) {
        const auto& resource = this->resources[i];
        glm::mat4 model = createModel(resource);
        glm::mat4 mvp = projection * view * model;

        glBindVertexArray(this->vertex_array_objects[i]);
        glUniformMatrix4fv(2, 1, GL_FALSE, glm::value_ptr(mvp));
        glDrawArrays(GL_TRIANGLES, 0, resource.object.vertices.size() / 3);
    }
}
