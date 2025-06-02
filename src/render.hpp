#pragma once
#include "glfwWindow.hpp"
#include "objects.hpp"
#include "physics.hpp"
#include "shader.hpp"
#include <string>
#include <vector>

class render : public physics
{
  public:
    render();
    void start(camera camera, float deltaT);
    rectangle test;
    sphere test1;
    class shader shader;
    void initializeAndUpdateMatrices(camera camera);

  public:
    void setRenderingConfig();
};
