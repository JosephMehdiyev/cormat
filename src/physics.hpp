#pragma once
#include "objects.hpp"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

const float g = 9.81f; // Earth gravity (m/s²)

class physics
{
  public:
    static inline glm::vec3 gravity{0.0f, -9.81f, 0.0f};
    void updateVelocity(object &object, float deltaT);
    void updatePosition(object &object, float deltaT);
    void update(object &object, float deltaT);
};
