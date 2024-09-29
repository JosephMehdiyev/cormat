#pragma once 
#include "glad.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>


class glfwCamera
{
                                    
public:
    glfwCamera(int screenWidth, int screenHeight);
    ~glfwCamera();
    GLFWwindow* window;
    // Handles input, movement, zoom, moving around etc.
    void processInput();
    void swapBuffers();
    void frameSizeCallBack(GLFWwindow* w, int width, int height);
    glm::vec3 cameraPosition,   // Position of camera in world system
              cameraRight,      // X axis of camera
              cameraUp,         // Y axis of camera
              cameraFront,      // Z axis of camera bu reversed i.e the direction camera looks at i.e negative z axis
                                // In openGL by convention camera direction is negative z axis
              worldUp;
    float cameraRotationSpeed;
    float cameraSpeed;

private:
    // Remark: these vectors are relative to camera system, except for cameraPosition
    // Could have made struct, but would be pointless anyways, since we would intiialize it once

    glm::mat4 GetViewMatrix;
                
    void processKeyboard();                                                                             
    void processMouseMovement();
    void processMouseScroll();
    void processZoom(GLFWwindow* window, double xoffset, double yoffset);
    void cursorCallBack(GLFWwindow* window, double xpos, double ypos);
    
    // Angles, used for rotating the camera
    // Yaw is Y axis
    // Pitch is X axis
    // Roll is Z axis
    float yaw, pitch, roll;
    bool firstMouse;

   

public:
    // Camera settings
    float movementSpeed, mouseSensitivity;      
    float fov;

    void updateCameraVectors();
    static void staticFrameSizeCallBack(GLFWwindow* w, int width, int height);
    static void staticScrollCallBack(GLFWwindow* w, double xoffset, double yoffset);
    static void staticCursorCallBack(GLFWwindow* w, double xpos, double ypos);
  

 double changeInX;
    double changeInY;
};
