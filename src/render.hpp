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
    engineFloor floor;
    sphere particle;
    class shader shader;
    void initializeAndUpdateMatrices(camera camera);
    bool isCollisionMode = false;

  public:
    void setRenderingConfig();
};
