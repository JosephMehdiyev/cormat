#include "glfwWindow.hpp"
#include <GLFW/glfw3.h>
#include <glm/geometric.hpp>
#include <iostream>

// https://www.songho.ca/opengl/gl_camera.html

glfwWindow::glfwWindow(int screenWidth, int screenHeight)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(screenWidth, screenHeight, "Cormat", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR);

    // NOTE: this is a workaround for OOP support. Since GLFW doesn't support class pointers (C library),
    //       we need new static function clones to use them as callbacks.
    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, staticFrameSizeCallBack);
    glfwSetScrollCallback(window, staticScrollCallBack);
    glfwSetCursorPosCallback(window, staticCursorCallBack);
}

glfwWindow::~glfwWindow()
{
}

void glfwWindow::getInput()
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        worldCamera.cameraPosition += worldCamera.cameraFront * worldCamera.cameraSpeed;

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        worldCamera.cameraPosition -= worldCamera.cameraFront * worldCamera.cameraSpeed;

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        worldCamera.cameraPosition -= glm::normalize(glm::cross(worldCamera.cameraFront, worldCamera.cameraUp)) * worldCamera.cameraSpeed;

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        worldCamera.cameraPosition += glm::normalize(glm::cross(worldCamera.cameraFront, worldCamera.cameraUp)) * worldCamera.cameraSpeed;

    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        worldCamera.cameraPosition += worldCamera.cameraUp * worldCamera.cameraSpeed;

    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        worldCamera.cameraPosition -= worldCamera.cameraUp * worldCamera.cameraSpeed;
}

void glfwWindow::swapBuffers()
{
    glfwSwapBuffers(window);
}

// WARNING: the rotation is relative to the object itself. What it does mean it that, after object
//          rotates 180* degrees, the rotation position gets reversed
void glfwWindow::cursorCallBack([[maybe_unused]] GLFWwindow *windoww, double xpos, double ypos)
{
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        float sensitivity = 2.0f;
        xpos *= sensitivity;
        ypos *= sensitivity;
        worldCamera.changeInX = xpos;
        worldCamera.changeInY = ypos;
    }
}

void glfwWindow::frameSizeCallBack([[maybe_unused]] GLFWwindow *w, int width, int height)
{
    glViewport(0, 0, width, height);
}

void glfwWindow::getZoomInput([[maybe_unused]] GLFWwindow *windoww, [[maybe_unused]] double xoffset, double yoffset)
{
    worldCamera.fov -= static_cast<float>(yoffset);
    if (worldCamera.fov < 1.0f)
        worldCamera.fov = 1.0f;
    if (worldCamera.fov > 45.0f)
        worldCamera.fov = 45.0f;
}

void glfwWindow::staticScrollCallBack(GLFWwindow *w, double xoffset, double yoffset)
{
    static_cast<glfwWindow *>(glfwGetWindowUserPointer(w))->getZoomInput(w, xoffset, yoffset);
}

void glfwWindow::staticFrameSizeCallBack(GLFWwindow *w, int width, int height)
{
    static_cast<glfwWindow *>(glfwGetWindowUserPointer(w))->frameSizeCallBack(w, width, height);
}

void glfwWindow::staticCursorCallBack(GLFWwindow *w, double xpos, double ypos)
{
    static_cast<glfwWindow *>(glfwGetWindowUserPointer(w))->cursorCallBack(w, xpos, ypos);
}
