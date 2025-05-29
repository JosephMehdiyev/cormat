#pragma once
#include <vector>
class render
{
  public:
    render();
    unsigned int VBO, VAO, EBO;
    void setBuffer(std::vector<float> vertice);
    void getNewVAO(std::vector<float> vertice);

  private:
    void initializeBuffer();
    void deleteBuffer();
};
