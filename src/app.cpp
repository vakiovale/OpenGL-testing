#include "app.h"

App::App() {
    spdlog::info("Creating App");
    AppConfiguration configuration;
    configuration.loadConfiguration("resources/config.json");
    this->conf = configuration.getConfig();

    if (!glfwInit()) {
        throw std::runtime_error("Could not initialize GLFW");
    }
}

App::~App() {
    glfwDestroyWindow(window);
    glfwTerminate();
    spdlog::info("App destroyed");
}

void App::run() {
    initializeWindow();
    Renderer renderer(window);
    this->object_resources = initializeResourceObjects();
    renderer.initialize(this->object_resources);

    while (!glfwWindowShouldClose(window)) {
        renderer.render();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void App::initializeWindow() {
    window = createWindow();
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
}

GLFWwindow* App::createWindow() {
    GLFWwindow* window =
        glfwCreateWindow(this->conf.width, this->conf.height, this->conf.name.c_str(), NULL, NULL);
    if (!window) {
        glfwTerminate();
    }
    return window;
}

