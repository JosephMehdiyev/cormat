#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

const float g = 9.81f; // Earth gravity (m/s²)

enum class bodyType
{
    STATIC,
    DYNAMIC,
};

struct rotation_degree
{
    float x, y, z;
};

class physics
{
  public:
    bodyType type = bodyType::DYNAMIC;
    float mass = 1.0f;
    static inline glm::vec3 gravity{0.0f, -9.81f, 0.0f};
    glm::vec3 velocity{0.0f, 0.0f, 0.0f};
    glm::vec3 acceleration{0.0f, 0.0f, 0.0f};
    glm::vec3 position{0.0f, 0.0f, 0.0f};
    struct rotation_degree rotation{0.0f, 0.0f, 0.0f};
    glm::vec3 scale = glm::vec3(1.0f);
};
