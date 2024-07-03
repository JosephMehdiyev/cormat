#pragma once 
#include "glad.h"
#include "glfw3.h"
#include <glm/glm.hpp>

class glfwWindow
{
    static void framebufferSizeCallback (GLFWwindow *window, int width, int height);

public:
    glfwWindow(int screenWidth, int screenHeight);
    GLFWwindow* window;
    // Handles the stuff when you increase your window size (for example, going full screen with f11 etc)
    // Handles input, movement, zoom, moving around etc.
    void processInput();
    void swapBuffers();
};