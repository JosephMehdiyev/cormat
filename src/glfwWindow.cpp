#include "glfwWindow.hpp"
#include "glfw3.h"
#include <tuple>
#include <iostream>


glfwWindow::glfwWindow(int screenWidth, int screenHeight)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // create glfw window
    
    window = glfwCreateWindow(screenWidth, screenHeight, "Cormat", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);

    //GLAD: load OPENGL function pointers
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }    

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

}

void 
glfwWindow::framebufferSizeCallback (GLFWwindow *window, int width, int height) 
{
    glViewport(0, 0, width, height);
    std::ignore = window;
}

void 
glfwWindow::processInput () 
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }   
    //const float cameraSpeed = 0.01f; 
    //if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    //{
    //    vec3 buffer;
    //    glm_vec3_scale(cameraFront, cameraSpeed, buffer);
    //    glm_vec3_add(cameraPos, buffer, cameraPos);
    //}
    //if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    //{
    //    vec3 buffer;
    //    glm_vec3_scale(cameraFront, cameraSpeed, buffer);
    //    glm_vec3_sub(cameraPos, buffer, cameraPos);
    //}
    //if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    //{
    //    vec3 buffer1, buffer2;
    //    glm_vec3_crossn(cameraFront, cameraUp, buffer1);
    //    glm_vec3_scale(buffer1, cameraSpeed, buffer2);
    //    glm_vec3_sub(cameraPos, buffer2, cameraPos);
    //}
    //if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    //{
    //    vec3 buffer1, buffer2;
    //    glm_vec3_crossn(cameraFront, cameraUp, buffer1);
    //    glm_vec3_scale(buffer1, cameraSpeed, buffer2);
    //    glm_vec3_add(cameraPos, buffer2, cameraPos);
    //}
    //if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    //{
    //    glm_vec3_add(cameraPos, cameraUp, cameraPos);
    //}
    //    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    //{
    //    glm_vec3_sub(cameraPos, cameraUp, cameraPos);
    //}
    //if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
    //{
    //    gridflag = false;
    //}
}

void
glfwWindow::swapBuffers()
{
    glfwSwapBuffers(window);
}








