#pragma once
#include "glad.h"
#include <GL/gl.h>
#include <vector>

class object;

class buffer
{
  public:
    buffer();
    ~buffer();
    unsigned int VBO, VAO, EBO;

  private:
    void initBuffer();
    void deleteBuffer();
};
