#include "app.h"

#include <string>

#include "GLFW/glfw3.h"
#include "input_handler.h"

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
    Camera camera;
    auto start = glm::vec3(0.0, 0.0, 0.0);
    auto end = glm::vec3(0.0, 0.0, -1.0);
    camera.position = start;
    camera.look_at = end;

    renderer.setCamera(camera);
    ObjectStorage storage(initializeResourceObjects());
    renderer.initialize(storage.getAll());

    double timer = glfwGetTime();
    const double PHYSICS_SPEED = 1.0f / 60.0f;
    double latest_time = 0;
    double current_time = 0;
    double delta_time = 0;
    uint frames = 0;

    InputHandler* const inputHandler = getInputHandler();
    inputHandler->setCamera(camera);
    double pos_x;
    double pos_y;
    glfwGetCursorPos(window_, &pos_x, &pos_y);
    inputHandler->setCursorPosition(pos_x, pos_y);
    glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetKeyCallback(window_, KEYCALLBACK);
    glfwSetCursorPosCallback(window_, CURSORCALLBACK);
    glfwSetCursorPos(window_, 0, 0);

    while (!glfwWindowShouldClose(window_)) {
        current_time = glfwGetTime();
        delta_time += (current_time - latest_time) / PHYSICS_SPEED;
        latest_time = current_time;

        renderer.render();
        glfwSwapBuffers(window_);
        glfwPollEvents();
        frames++;

        while (delta_time >= 1.0) {
            //            storage.translateAll(glm::vec3(0.0, 0.0, PHYSICS_SPEED));
            // camera.position += glm::normalize(end - start) * (float)PHYSICS_SPEED*20.0f;
            delta_time--;
        }

        if (glfwGetTime() - timer > 1.0) {
            spdlog::info("FPS " + std::to_string(frames));
            frames = 0;
            timer = glfwGetTime();
        }
    }
}

void App::initializeWindow() {
    window_ = createWindow();
    glfwMakeContextCurrent(window_);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
}

GLFWwindow* App::createWindow() {
    glfwWindowHint(GLFW_REFRESH_RATE, GLFW_DONT_CARE);
    GLFWwindow* window =
        glfwCreateWindow(conf_.width, conf_.height, conf_.name.c_str(), NULL, NULL);
    if (!window) {
        glfwTerminate();
    }
    return window;
}
