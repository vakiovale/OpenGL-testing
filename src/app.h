#ifndef APP_H_
#define APP_H_

#include <glad/glad.h>
#include <spdlog/spdlog.h>

#include <boost/property_tree/json_parser.hpp>
#include <iostream>

#include "glfw.h"
#include "object_loader.h"
#include "object_resource.h"
#include "renderer.h"

class App {
   private:
    GLFWwindow* window;
    std::vector<object_resource> object_resources;
    GLFWwindow* createWindow();
    void initializeWindow();
    void initializeResourceObjects();

   public:
    App();
    ~App();
    void run();
};

#endif
