#pragma once
#include "glad.h"
#include <GL/gl.h>
#include <vector>

class buffer
{
  public:
    buffer();
    ~buffer();
    unsigned int VBO, VAO, EBO;
    void setBuffer(std::vector<float> coordData, std::vector<unsigned int> indiceData, std::vector<float> textureData);

  private:
    void initBuffer();
    void deleteBuffer();
};
