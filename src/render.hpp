#pragma once
#include "glfwWindow.hpp"
#include "objects.hpp"
#include "shader.hpp"
#include <string>
#include <vector>

class render
{
  public:
    render();
    void start(camera camera);
    sphere test;
    rectangle test1;
    class shader shader;
    void initializeAndUpdateMatrices(camera camera);

  public:
    void setRenderingConfig();
};
