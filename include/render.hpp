#pragma once

class render
{
    void deleteBuffer();
public:
    render();
    void initializeBuffer();
    void initializeBufferLine();
    unsigned int VBO, VAO, EBO;
};
