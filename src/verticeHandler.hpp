#pragma once
#include "glad.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>

#define BLACK 0.0f, 0.0f, 0.0f
#define WHITE 1.0f, 1.0f, 1.0f
#define RED 1.0f, 0.0f, 0.0f
#define GREEN 0.0f, 1.0f, 0.0f
#define BLUE 0.0f, 0.0f, 1.0f

struct vertice
{
    std::vector<float> posCoord;
    std::vector<float> colCoord;
    std::vector<float> texturCoord; // may be empty
};

class verticeData
{
    verticeData();

  public:
    std::vector<float> rawDataTest;
    std::vector<vertice> rawData;
    std::vector<float> cleanData;
    std::vector<float> getCleanData(std::vector<vertice> rawData);
};
