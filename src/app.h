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
    Configuration conf_;
    GLFWwindow* window_;
    std::vector<ObjectResource> object_resources_;
    GLFWwindow* createWindow();
    void initializeWindow();

   public:
    App();
    ~App();
    void run();
};

#endif
