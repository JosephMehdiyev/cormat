#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

const float g = 9.81f; // Earth gravity (m/s²)

enum class bodyType
{
    STATIC,
    DYNAMIC,
};

class physics
{
  public:
    bodyType type = bodyType::DYNAMIC;
    float mass = 1.0f;
    static inline glm::vec3 gravity{0.0f, -9.81f, 0.0f};
    glm::vec3 velocity{0.0f, -0.3f, 0.0f};
    glm::vec3 acceleration;
    glm::vec3 position{0.0f, 5.0f, 0.0f};
};
