#include "render.hpp"
#include "glad.h"
#include <GL/gl.h>


render::render()
{
    this->initializeBuffer();
}
void
render::initializeBuffer()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
}

void
render::setBuffer(std::vector<float> vertice)
{
    glBindVertexArray(VAO);
    glBufferData(GL_ARRAY_BUFFER, static_cast<long long int>(6* sizeof(float) * vertice.size()), &vertice[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void*>(0));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void*>(3*sizeof(float)));
    glEnableVertexAttribArray(1);
}

void
render::deleteBuffer()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}


