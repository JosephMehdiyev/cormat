#pragma once
#include "glfwCamera.hpp"
#include "render.hpp"
#include "shader.hpp"
#include <string>
#include <vector>
class graph
{
  public:
    graph(int numberOfBoxes);
    void start(glfwCamera glfwCamera);
    std::vector<float> gridVertices;

    class render render;
    class shader shader;
    int n;
    void initializeAndUpdateShaders(glfwCamera glfwCamera);

  public:
    void draw();
    int totalBoxes;
    std::vector<float> findPairSymmetry(std::vector<float> vec, std::string axis);

    void setRenderingConfig();
    void pointGenerator();
};
