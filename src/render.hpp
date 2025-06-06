#pragma once
#include "entity.hpp"
#include "glfwWindow.hpp"
#include "physics.hpp"
#include "rectangle.hpp"
#include "shader.hpp"
#include "sphere.hpp"
#include <string>
#include <vector>

class render : public physics
{
  public:
    render();
    void start(camera camera, float deltaT);
    std::vector<std::unique_ptr<entity>> entities;

    class shader shader;
    void initializeAndUpdateMatrices(camera camera);
    bool isCollisionMode = false;
    bool startUpdatingPhysics = true;

  public:
    void setRenderingConfig();
};
