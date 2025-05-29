#pragma once
#include "glad.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class glfwCamera
{
  public:
    glfwCamera(int screenWidth, int screenHeight);
    ~glfwCamera();
    GLFWwindow *window;
    void getInput();
    void swapBuffers();
    void frameSizeCallBack(GLFWwindow *w, int width, int height);
    glm::vec3 cameraPosition, cameraRight, cameraUp, cameraFront, worldUp;
    float cameraRotationSpeed;
    float cameraSpeed;

  private:
    glm::mat4 GetViewMatrix;
    void getKeyboard();
    void getMouseMovement();
    void getMouseScroll();
    void getZoomInput(GLFWwindow *window, double xoffset, double yoffset);
    void cursorCallBack(GLFWwindow *window, double xpos, double ypos);

    // Angles, used for rotating the camera
    // Yaw is Y axis
    // Pitch is X axis
    // Roll is Z axis
    float rotationY, rotationX, rotationZ;
    bool firstMouse;

  public:
    // Camera settings
    float movementSpeed, mouseSensitivity;
    float fov;

    void updateCameraVectors();
    static void staticFrameSizeCallBack(GLFWwindow *w, int width, int height);
    static void staticScrollCallBack(GLFWwindow *w, double xoffset, double yoffset);
    static void staticCursorCallBack(GLFWwindow *w, double xpos, double ypos);

    double changeInX;
    double changeInY;
};
