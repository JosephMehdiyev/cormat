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

class cube
{
  public:
    cube();
    std::vector<float> coordData;
    std::vector<unsigned int> indiceData;
    glm::mat4 modelMatrix;
};
