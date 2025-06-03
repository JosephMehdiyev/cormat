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
