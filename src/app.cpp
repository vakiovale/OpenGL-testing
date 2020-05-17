#include "app.h"

void App::run() {
    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit()) {
        return;
    }
    
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window) {
        glfwTerminate();
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    Renderer renderer;
    renderer.initialize();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        renderer.render();

        /* Swap Front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}
