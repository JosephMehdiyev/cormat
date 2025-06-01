#include "render.hpp"
#include <GL/gl.h>
#include <stdexcept>

buffer::buffer()
{
    initBuffer();
}
void

buffer::initBuffer()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    unsigned int err = glGetError();
    if (err != GL_NO_ERROR)
    {
        deleteBuffer();
        throw std::runtime_error("Failed to Generate OpenGL Buffers: " + std::to_string(err));
    }
}

void buffer::setBuffer(std::vector<float> coordData, std::vector<unsigned int> indiceData, std::vector<float> textureData)
{
    if (coordData.empty())
        throw std::invalid_argument("Vertice Data Cannot be Empty");
    if (indiceData.empty())
        throw std::invalid_argument("Indice Data Cannot be Empty");
    if (textureData.empty())
    {
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, static_cast<long long int>(sizeof(float) * coordData.size()), &coordData[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<long long int>(sizeof(unsigned int) * indiceData.size()), &indiceData[0], GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void *>(0));
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void *>(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        unsigned int err = glGetError();
        if (err != GL_NO_ERROR)
        {
            throw std::runtime_error("Failed to set Vertice or Indice Data to Buffers: " + std::to_string(err));
        }
    }
    else
    {
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, static_cast<long long int>(sizeof(float) * coordData.size()), &coordData[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<long long int>(sizeof(unsigned int) * indiceData.size()), &indiceData[0], GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void *>(0));
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void *>(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void *>(6 * sizeof(float)));
        glEnableVertexAttribArray(2);
        unsigned int err = glGetError();
        if (err != GL_NO_ERROR)
        {
            throw std::runtime_error("Failed to set Vertice or Indice Data to Buffers: " + std::to_string(err));
        }
    }
}

void buffer::deleteBuffer()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

buffer::~buffer()
{
    deleteBuffer();
}
