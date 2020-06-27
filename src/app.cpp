#include "app.h"

App::App() {
    spdlog::info("Creating App");
    AppConfiguration configuration;
    configuration.loadConfiguration("resources/config.json");
    conf_ = configuration.getConfig();

    if (!glfwInit()) {
        throw std::runtime_error("Could not initialize GLFW");
    }
}

App::~App() {
    glfwDestroyWindow(window_);
    glfwTerminate();
    spdlog::info("App destroyed");
}

void App::run() {
    initializeWindow();
    Renderer renderer(window_);
    object_resources_ = initializeResourceObjects();
    renderer.initialize(object_resources_);

    while (!glfwWindowShouldClose(window_)) {
        renderer.render();
        glfwSwapBuffers(window_);
        glfwPollEvents();
    }
}

void App::initializeWindow() {
    window_ = createWindow();
    glfwMakeContextCurrent(window_);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
}

GLFWwindow* App::createWindow() {
    GLFWwindow* window =
        glfwCreateWindow(conf_.width, conf_.height, conf_.name.c_str(), NULL, NULL);
    if (!window) {
        glfwTerminate();
    }
    return window;
}

