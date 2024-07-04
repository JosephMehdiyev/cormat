#pragma once

class render
{
    void deleteBuffer();
public:
    render();
    void initializeBuffer();
    unsigned int VBO, VAO, EBO;
};