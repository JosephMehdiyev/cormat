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
    float rotationY, rotationX, rotationZ;
    float movementSpeed, mouseSensitivity;
    float fov;
    double changeInX;
    double changeInY;

    void updateCameraVectors();
};
