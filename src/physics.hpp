#pragma once
#include "collision.hpp"
#include "entity.hpp"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

const float g = 9.81f; // Earth gravity (m/s²)

class physics
{
  public:
    static inline glm::vec3 gravity{0.0f, -9.81f, 0.0f};
    void updateVelocity(std::unique_ptr<entity> &object, float deltaT);
    void updatePosition(std::unique_ptr<entity> &object, float deltaT);
    void update(std::vector<std::unique_ptr<entity>> &entities, float deltaT);
};
