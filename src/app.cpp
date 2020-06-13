#include "app.h"

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
    GLFWwindow* window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);
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

void App::initializeResourceObjects() {
    try {
        boost::property_tree::ptree json;
        boost::property_tree::read_json("resources/objects.json", json);
        auto objects = json.get_child("objects");

        for (auto& obj : objects) {
            object_resource result;
            std::string file = obj.second.get<std::string>("file");
            result.file = file;
            result.object = loadObject(file);
            auto translate = obj.second.get_child("translate");
            result.translate =
                glm::vec3(translate.get<float>("x"), translate.get<float>("y"),
                          translate.get<float>("z"));
            object_resources.push_back(result);
        }
    } catch (const std::exception& exception) {
        spdlog::error("Failed parsing json: " + std::string(exception.what()));
        throw exception;
    }
}

void App::run() {
    initializeWindow();
    Renderer renderer(window);
    initializeResourceObjects();
    renderer.initialize(this->object_resources);

    while (!glfwWindowShouldClose(window)) {
        renderer.render();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
