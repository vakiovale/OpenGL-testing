#include "main.h"

int main() {
    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit()) {
        return 0;
    }

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window) {
        glfwTerminate();
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        render();

        /* Swap Front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
