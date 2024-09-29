#include "glfwCamera.hpp"
#include <GLFW/glfw3.h>
#include <glm/geometric.hpp>
#include <iostream>

// https://www.songho.ca/opengl/gl_camera.html

glfwCamera::glfwCamera(int screenWidth, int screenHeight)
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
    
    //NOTE: this is a workaround for OOP support. Since GLFW doesn't support class pointers (C library),
    //      we need new static function clones to use them as callbacks.
    glfwSetWindowUserPointer(window, this);        
    glfwSetFramebufferSizeCallback(window, staticFrameSizeCallBack);
    glfwSetScrollCallback(window, staticScrollCallBack);
    glfwSetCursorPosCallback(window, staticCursorCallBack);





    // Camera Part
    // --------------------------------------------------------------------------
        cameraPosition = glm::vec3(0.0f,0.0f,1.0f);
        cameraRotationSpeed = 0.2;
        worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
        cameraFront = glm::vec3(0.0,0.0, 1.0);
        yaw = -90.0f;
        pitch =  0.0f;
        roll = 0.0f;
        updateCameraVectors();  
        firstMouse = true;
        fov = 60.0f;
        cameraSpeed = 0.05f; 

    

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
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        cameraPosition += cameraFront * cameraSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        cameraPosition -= cameraFront * cameraSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        cameraPosition -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        cameraPosition += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        cameraPosition += cameraUp * cameraSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        cameraPosition -= cameraUp * cameraSpeed;
    }


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


// WARNING: the rotation is relative to the object itself. What it does mean it that, after object 
//          rotates 180* degrees, the rotation position gets reversed
// FIXME:   fix the warning
void 
glfwCamera::cursorCallBack( [[maybe_unused]] GLFWwindow* windoww, double xpos, double ypos)
{
   if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
    float sensitivity = 2.0f;
    xpos *= sensitivity;
    ypos *= sensitivity;
    changeInX = xpos;
    changeInY = ypos;}
}


void
glfwCamera::frameSizeCallBack([[maybe_unused]] GLFWwindow* w, int width, int height) 
{
     glViewport(0, 0, width, height);
}


void    
glfwCamera::processZoom( [[maybe_unused]] GLFWwindow* windoww, [[maybe_unused]] double xoffset, double yoffset)
{
    glfwCamera::fov -= static_cast<float>(yoffset);                        
    if (fov < 1.0f) glfwCamera::fov = 1.0f;
    if(fov > 45.0f) glfwCamera::fov = 45.0f;
}


// NOTE: these are  our static function clones. Do not touch!
void
glfwCamera::staticScrollCallBack(GLFWwindow *w, double xoffset, double yoffset)
{
     static_cast<glfwCamera*>(glfwGetWindowUserPointer(w))->processZoom( w, xoffset, yoffset);
}


void
glfwCamera::staticFrameSizeCallBack(GLFWwindow* w, int width, int height) 
{ 
    static_cast<glfwCamera*>(glfwGetWindowUserPointer(w))->frameSizeCallBack(w, width, height);
}


void
glfwCamera::staticCursorCallBack(GLFWwindow *w, double xpos, double ypos)
{
    static_cast<glfwCamera*>(glfwGetWindowUserPointer(w))->cursorCallBack(w, xpos, ypos);
}





