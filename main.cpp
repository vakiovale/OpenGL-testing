#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/common.hpp>

#include <cmath>
#include <iostream>

int main()
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        const float redValue = sin(glfwGetTime()) * 0.5f + 0.5f;
        const float greenValue = cos(glfwGetTime() + M_PI/2) * 0.5f + 0.5f;
        const GLfloat red[] = {redValue, greenValue, 0.0f, 1.0f};
        glClearBufferfv(GL_COLOR, 0, red);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
