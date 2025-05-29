#include "camera.hpp"
#include <GLFW/glfw3.h>
#include <glm/geometric.hpp>
#include <iostream>

camera::camera()
{
    // Camera's Initial values
    cameraPosition = glm::vec3(0.0f, 0.0f, 1.0f);
    cameraRotationSpeed = 0.2;
    worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    cameraFront = glm::vec3(0.0, 0.0, 1.0);
    rotationY = -90.0f;
    rotationX = 0.0f;
    rotationZ = 0.0f;
    updateCameraVectors();
    firstMouse = true;
    fov = 60.0f;
    cameraSpeed = 0.05f;
}

void camera::updateCameraVectors()
{
    glm::vec3 bufferCameraFront;
    bufferCameraFront.x = cos(glm::radians(rotationY)) * cos(glm::radians(rotationX));
    bufferCameraFront.y = sin(glm::radians(rotationX));
    bufferCameraFront.z = sin(glm::radians(rotationY)) * cos(glm::radians(rotationX));
    cameraFront = glm::normalize(bufferCameraFront);

    cameraRight = glm::normalize(glm::cross(cameraFront, worldUp));
    cameraUp = glm::normalize(glm::cross(cameraRight, cameraFront));
}
