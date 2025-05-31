#pragma once
#include <vector>
class buffer
{
  public:
    buffer();
    unsigned int VBO, VAO, EBO;
    void setBuffer(std::vector<float> coordData, std::vector<unsigned int> indiceData);
    void getNewVAO(std::vector<float> vertice);

  private:
    void initBuffer();
    void deleteBuffer();
};
