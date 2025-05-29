#pragma once
#include "glad.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class camera
{
  public:
    camera();
    glm::vec3 cameraPosition, cameraRight, cameraUp, cameraFront, worldUp;
    float cameraRotationSpeed;
    float cameraSpeed;
    // Angles, used for rotating the camera
    // Yaw is Y axis
    // Pitch is X axis
    // Roll is Z axis
    float rotationY, rotationX, rotationZ;
    bool firstMouse;
    // Camera settings
    float movementSpeed, mouseSensitivity;
    float fov;
    double changeInX;
    double changeInY;

    void updateCameraVectors();
};
