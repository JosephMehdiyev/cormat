#pragma once
#include "objects.hpp"
#include <vector>
class buffer
{
  public:
    buffer();
    unsigned int VBO, VAO, EBO;
    void setBuffer(object shape);
    void getNewVAO(std::vector<float> vertice);

  private:
    void initBuffer();
    void deleteBuffer();
};
