#include "camera.hpp"
#include <GLFW/glfw3.h>
#include <glm/geometric.hpp>

camera::camera()
{
    // Camera's Initial values
    cameraPosition = glm::vec3(0.2f, 0.2f, 1.2f);
    cameraRotationSpeed = 0.2;
    worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    cameraFront = glm::vec3(0.0, 0.0, 1.0);
    rotationY = -90.0f;
    rotationX = 0.0f;
    rotationZ = 0.0f;
    updateCameraVectors();
    fov = 60.0f;
    changeInX = 0;
    changeInY = 0;
    cameraSpeed = 0.3f;
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
