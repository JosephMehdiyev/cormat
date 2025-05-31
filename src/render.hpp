#pragma once
#include "objects.hpp"
#include <vector>
class render
{
  public:
    render();
    unsigned int VBO, VAO, EBO;
    void setBuffer(cube shape);
    void getNewVAO(std::vector<float> vertice);

  private:
    void initBuffer();
    void deleteBuffer();
};
