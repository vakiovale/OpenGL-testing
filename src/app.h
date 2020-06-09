#ifndef APP_H_
#define APP_H_

#include <glad/glad.h>
#include <spdlog/spdlog.h>

#include <iostream>

#include "glfw.h"
#include "renderer.h"

class App {
   private:
    GLFWwindow* window;
    GLFWwindow* createWindow();
    void initializeWindow();

   public:
    App();
    ~App();
    void run();
};

#endif
