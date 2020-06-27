#ifndef APP_H_
#define APP_H_

#include <glad/glad.h>
#include <spdlog/spdlog.h>

#include <iostream>

#include "app_configuration.h"
#include "glfw.h"
#include "object_resource.h"
#include "renderer.h"

class App {
   private:
    configuration conf;
    GLFWwindow* window;
    std::vector<ObjectResource> object_resources;
    GLFWwindow* createWindow();
    void initializeWindow();

   public:
    App();
    ~App();
    void run();
};

#endif
