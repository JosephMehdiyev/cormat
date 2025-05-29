#pragma once
#include "glfwWindow.hpp"
#include "render.hpp"
#include "shader.hpp"
#include <string>
#include <vector>
class graph
{
  public:
    graph(int numberOfBoxes);
    void start(camera camera);
    std::vector<float> gridVertices;

    class render render;
    class shader shader;
    int n;
    void initializeAndUpdateShaders(camera camera);

  public:
    void draw();
    int totalBoxes;
    std::vector<float> findPairSymmetry(std::vector<float> vec, std::string axis);

    void setRenderingConfig();
    void pointGenerator();
};
