#include "app.h"
#include <exception>
#include <stdexcept>
#include "renderer.h"
#include "spdlog/spdlog.h"

App::App() {
    spdlog::info("Creating App");

    if (!glfwInit()) {
        throw std::runtime_error("Could not initialize GLFW");
    }
}

void App::initializeWindow() {
    window = createWindow();
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
}

GLFWwindow* App::createWindow() {
    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window) {
        glfwTerminate();
    }
    return window;
}

App::~App() {
    glfwDestroyWindow(window);
    glfwTerminate();
    spdlog::info("App destroyed");
}

void App::run() {
    initializeWindow();
    Renderer renderer(window);
    renderer.initialize();
    
    while (!glfwWindowShouldClose(window)) {
        renderer.render();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

}
