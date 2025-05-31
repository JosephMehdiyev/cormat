#pragma once
#include "buffer.hpp"
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
    cube test;
    class buffer buffer;
    class shader shader;
    void initializeAndUpdateShaders(camera camera);

  public:
    void draw();
    void setRenderingConfig();
};
