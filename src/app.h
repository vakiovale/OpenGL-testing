#ifndef APP_H_
#define APP_H_

#include <glad/glad.h>
#include <spdlog/spdlog.h>

#include <iostream>

#include "GLFW/glfw3.h"
#include "app_configuration.h"
#include "glfw.h"
#include "object_resource.h"
#include "object_storage.h"
#include "renderer.h"
#include "input_handler.h"

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
