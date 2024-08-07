#pragma once
#include <vector>
class render
{
    void deleteBuffer();
public:
    render();
    void setBufferLine();
    unsigned int VBO, VAO, EBO;
    void setBuffer(std::vector<float> vertice);
private:
    void initializeBuffer();
};
