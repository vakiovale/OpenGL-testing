#include "renderer.h"
#include "glm/gtc/quaternion.hpp"

Renderer::Renderer(GLFWwindow* window) : window(*window) {}

Renderer::~Renderer() {
    glDeleteBuffers(vertex_buffer_objects_.size(), vertex_buffer_objects_.data());
    glDeleteVertexArrays(vertex_array_objects_.size(), vertex_array_objects_.data());
    glDeleteProgram(program_);
    spdlog::info("Renderer destroyed");
}

void Renderer::setCamera(const Camera& camera) {
    camera_ = &camera;
}

void Renderer::createProgram() {
    program_ = glCreateProgram();

    createVertexShader(program_);
    createFragmentShader(program_);

    glLinkProgram(program_);
    glUseProgram(program_);
}

void Renderer::createShader(GLuint program, std::string file, GLenum shader_type) {
    GLuint shader = glCreateShader(shader_type);
    const std::string shader_source = file_loader_.load("resources/glsl/" + file);
    const GLchar* source = shader_source.c_str();
    spdlog::debug("Loaded shader:\n" + shader_source);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
    glAttachShader(program, shader);
    glDeleteShader(shader);
}

void Renderer::createVertexShader(GLuint program) {
    createShader(program, "vertex_shader.glsl", GL_VERTEX_SHADER);
}

void Renderer::createFragmentShader(GLuint program) {
    createShader(program, "fragment_shader.glsl", GL_FRAGMENT_SHADER);
}

glm::mat4 Renderer::selectCameraLens(float field_of_view) const {
    return glm::perspective(glm::radians(field_of_view), (float)width_ / (float)height_, 0.1f,
                            10000.0f);
}

glm::mat4 Renderer::setupCameraPosition() const {
    return glm::mat4_cast(camera_->orientation) * glm::translate(glm::mat4(1.0), camera_->position);
    //return glm::lookAt(camera_->position, camera_->look_at, camera_->rotation);
}

glm::mat4 Renderer::setupModel() const {
    glm::mat4 model = glm::mat4(1.0f);
    const float angle = glfwGetTime() * 1.0f;
    glm::mat4 new_translate = glm::translate(glm::vec3(0.0f, sin(angle) * 10.0f, 0.0f));
    glm::mat4 scale = glm::scale(glm::vec3(10.0f));
    glm::mat4 rotate = glm::rotate(angle, glm::vec3(0.0f, 1.0f, 0.0f));
    return new_translate * rotate * scale * model;
}

void Renderer::createVAOsAndGenerateBuffers() {
    GLuint vaos[resources_->size()];
    GLuint buffers[resources_->size()];
    glCreateVertexArrays(resources_->size(), vaos);
    glGenBuffers(resources_->size(), buffers);

    for (std::size_t i = 0; i < resources_->size(); i++) {
        vertex_array_objects_.push_back(vaos[i]);
        vertex_buffer_objects_.push_back(buffers[i]);
    }
}

void Renderer::loadAndBindObject(const ObjectResource& resource, const GLuint VAO,
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

void Renderer::initialize(std::vector<ObjectResource>& resources) {
    spdlog::info("Initializing OpenGL");
    enableDebug();

    resources_ = &resources;

    glfwGetWindowSize(&window, &width_, &height_);

    createProgram();
    createVAOsAndGenerateBuffers();

    spdlog::info("Load and bind objects");
    for (std::size_t i = 0; i < resources_->size(); i++) {
        loadAndBindObject((*resources_)[i], vertex_array_objects_[i], vertex_buffer_objects_[i]);
    }
    spdlog::info("Loading objects finished");

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glFrontFace(GL_CCW);
    // glEnable(GL_CULL_FACE);
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

glm::mat4 Renderer::createModel(const ObjectResource& resource) const {
    glm::mat4 translate =
        glm::translate(resource.position);
    glm::mat4 scale = glm::scale(resource.scale);
    glm::mat4 rotate = glm::rotate(1.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    return translate * rotate * scale;
}

void Renderer::draw() {
    glm::mat4 projection = selectCameraLens(80.0f);
    glm::mat4 view = setupCameraPosition();

    for (std::size_t i = 0; i < resources_->size(); i++) {
        const auto& resource = (*resources_)[i];
        glm::mat4 model = createModel(resource);
        glm::mat4 mvp = projection * view * model;

        glBindVertexArray(vertex_array_objects_[i]);
        glUniformMatrix4fv(2, 1, GL_FALSE, glm::value_ptr(mvp));
        glDrawArrays(GL_TRIANGLES, 0, resource.object.vertices.size() / 3);
    }
}
