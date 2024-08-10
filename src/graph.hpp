#pragma once
#include <vector>
#include <string>
#include "render.hpp"
#include "shader.hpp"
#include "glfwCamera.hpp"
class graph
{
public:
    graph(int numberOfBoxes);
    void start(glfwCamera glfwCamera);

private:
    void draw();
    int totalBoxes;
    std::vector<float> gridVertices;
    std::vector<float> findPairSymmetry(std::vector<float> vec, std::string axis);
    class render render;
    class shader shader;
    void initializeAndUpdateShaders(glfwCamera glfwCamera);
    void setRenderingConfig();
};
