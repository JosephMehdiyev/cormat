#pragma once
#include <vector>
#include <string>
#include "render.hpp"
class graph
{
public:
    graph(int numberOfBoxes);
    void draw();

private:
    int totalBoxes;
    std::vector<float> gridVertices;
    std::vector<float> findPairSymmetry(std::vector<float> vec, std::string axis);
    class render render;
};
