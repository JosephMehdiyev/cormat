#pragma once
#include "camera.hpp"
#include "glad.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <sstream>

#define GAME_NAME "Cormat"
#define VERSION "0.1.1-alpha"

class glfwWindow
{
  public:
    glfwWindow(int screenWidth, int screenHeight);
    ~glfwWindow();
    camera worldCamera;
    void getInput();
    void swapBuffers();
    void frameSizeCallBack(GLFWwindow *w, int width, int height);
    GLFWwindow *window;
    float FPS;
    unsigned int nbFrames;
    void showFPS();

  private:
    float elapsedTime;
    float lastTime = 0;
    glm::mat4 GetViewMatrix;
    void getKeyboard();
    void getMouseMovement();
    void getMouseScroll();
    void getZoomInput(GLFWwindow *window, double xoffset, double yoffset);
    void cursorCallBack(GLFWwindow *window, double xpos, double ypos);
    float lastCursorPositionX, lastCursorPositionY;

  public:
    static void staticFrameSizeCallBack(GLFWwindow *w, int width, int height);
    static void staticScrollCallBack(GLFWwindow *w, double xoffset, double yoffset);
    static void staticCursorCallBack(GLFWwindow *w, double xpos, double ypos);
};
