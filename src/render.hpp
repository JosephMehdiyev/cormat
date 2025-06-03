#pragma once
#include "glfwWindow.hpp"
#include "objects.hpp"
#include "sphere.hpp"
#include "physics.hpp"
#include "shader.hpp"
#include "rectangle.hpp"
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

  public:
    void setRenderingConfig();
};
