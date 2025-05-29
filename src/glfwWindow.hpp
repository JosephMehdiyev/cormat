#pragma once
#include "camera.hpp"
#include "glad.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class glfwWindow
{
  public:
    glfwWindow(int screenWidth, int screenHeight);
    ~glfwWindow();
    camera worldCamera;
    GLFWwindow *window;
    void getInput();
    void swapBuffers();
    void frameSizeCallBack(GLFWwindow *w, int width, int height);

  private:
    glm::mat4 GetViewMatrix;
    void getKeyboard();
    void getMouseMovement();
    void getMouseScroll();
    void getZoomInput(GLFWwindow *window, double xoffset, double yoffset);
    void cursorCallBack(GLFWwindow *window, double xpos, double ypos);

  public:
    static void staticFrameSizeCallBack(GLFWwindow *w, int width, int height);
    static void staticScrollCallBack(GLFWwindow *w, double xoffset, double yoffset);
    static void staticCursorCallBack(GLFWwindow *w, double xpos, double ypos);
};
