#include "glfwCamera.hpp"
#include "glfw3.h"
#include <glm/geometric.hpp>
#include <iostream>

// https://www.songho.ca/opengl/gl_camera.html

glfwCamera::glfwCamera(int screenWidth, int screenHeight)
{
    // Window Part
    // ----------------------------------------------------------------
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
    glfwSetWindowUserPointer(window, this);        
    glfwSetFramebufferSizeCallback(window, staticFrameSizeCallBack);
    glfwSetScrollCallback(window, staticScrollCallBack);
    glfwSetCursorPosCallback(window, staticCursorCallBack);





    // Camera Part
    // --------------------------------------------------------------------------
        cameraPosition = glm::vec3(0.0f,0.0f,0.0f);
        worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
        yaw = -90.0f;
        pitch =  0.0f;
        roll = 0.0f;
        updateCameraVectors();  

}
glfwCamera::~glfwCamera()
{

}


void 
glfwCamera::processInput() 
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
glfwCamera::swapBuffers()
{
    glfwSwapBuffers(window);
}

void 
glfwCamera::updateCameraVectors()
{   
    glm::vec3 bufferCameraFront;
    bufferCameraFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    bufferCameraFront.y = sin(glm::radians(pitch));
    bufferCameraFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(bufferCameraFront);

    cameraRight = glm::normalize(glm::cross(cameraFront, worldUp));
    cameraUp = glm::normalize(glm::cross(cameraRight, cameraFront));
}


void 
glfwCamera::cursorCallBack( [[maybe_unused]] GLFWwindow* windoww, double xpos, double ypos)
{

    float sensitivity = 0.01f;
    xpos *= sensitivity;
    ypos *= sensitivity;

    yaw += xpos;
    pitch += ypos;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;
    updateCameraVectors();
}


void    
glfwCamera::processZoom( [[maybe_unused]] GLFWwindow* windoww, [[maybe_unused]] double xoffset, double yoffset)
{
    glfwCamera::fov -= static_cast<float>(yoffset);                        
    if (fov < 1.0f) glfwCamera::fov = 1.0f;
    if(fov > 45.0f) glfwCamera::fov = 45.0f;
}

void
glfwCamera::staticScrollCallBack(GLFWwindow *w, double xoffset, double yoffset)
{
     static_cast<glfwCamera*>(glfwGetWindowUserPointer(w))->processZoom( w, xoffset, yoffset);
}


void
glfwCamera::staticFrameSizeCallBack(GLFWwindow* w, int width, int height) 
{ 
    //set this in window init
    static_cast<glfwCamera*>(glfwGetWindowUserPointer(w))->frameSizeCallBack(w, width, height);
}


void
glfwCamera::frameSizeCallBack([[maybe_unused]] GLFWwindow* w, int width, int height) 
{
     glViewport(0, 0, width, height);
}


void
glfwCamera::staticCursorCallBack(GLFWwindow *w, double xpos, double ypos)
{
    static_cast<glfwCamera*>(glfwGetWindowUserPointer(w))->cursorCallBack(w, xpos, ypos);
}





