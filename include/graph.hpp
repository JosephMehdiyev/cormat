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
    class render render;
};
