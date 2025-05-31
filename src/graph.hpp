#pragma once
#include "glfwWindow.hpp"
#include "render.hpp"
#include "shader.hpp"
#include <string>
#include <vector>
class graph
{
  public:
    graph();
    void start(camera camera);

    class render render;
    class shader shader;
    void initializeAndUpdateShaders(camera camera);

  public:
    void draw();
    void setRenderingConfig();
};
