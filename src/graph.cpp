#include "graph.hpp"
#include "glm/glm.hpp"
#include "glad.h"
#include <GL/gl.h>
#include <vector>
#include <iostream>

graph::graph(int numberOfBoxes) {
  totalBoxes = numberOfBoxes;

  // NOTE: each vector represents a vertices with its 6 float data.
  //      first 3 floats represent the position in normal coordinates.
  //      later 3 floats represent the color of the vertice.
  //      2 vertices are in the group to draw a line.
  gridVertices = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
                  -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,

                  0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
                  0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f,

                  0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
                  0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f};

  for (int i = 0; i < totalBoxes + 1; i++)
  {
      std::vector<float> vec(6);
      std::vector<float> vec2(6);

      vec[0] = -1.0f + static_cast<float>(i) / totalBoxes * 2.0f;
      vec[1] = +1.0f;
      vec[2] = 0.0f;
      vec[3] = 0.0;
      vec[4] = 0.0;
      vec[5] = 0.0;
      vec2 = findPairSymmetry(vec, "X");
      for (unsigned int j = 0; j < 6; j++)
      {
          gridVertices.push_back(vec[j]);
      }

      for (unsigned int j = 0; j <6 ; j++)
      {
          gridVertices.push_back(vec2[j]);
      }
  }

    for (int i = 0; i < totalBoxes + 1; i++)
  {
      std::vector<float> vec(6);
      std::vector<float> vec2(6);

      vec[0] = -1.0f ;
      vec[1] = +1.0f - static_cast<float>(i) / totalBoxes * 2.0f;
      vec[2] = 0.0f;
      vec[3] = 0.0;
      vec[4] = 0.0;
      vec[5] = 0.0;
      vec2 = findPairSymmetry(vec, "Y");
      for (unsigned int j = 0; j < 6; j++)
      {
          gridVertices.push_back(vec[j]);
      }

      for (unsigned int j = 0; j <6 ; j++)
      {
          gridVertices.push_back(vec2[j]);
      }
  }

  render.setBuffer(gridVertices);
}

std::vector<float> graph::findPairSymmetry(std::vector<float> vec,
                                           std::string axis) {
  int x, y;
  if (axis == "X") {
    x = -1, y = 1;
  }
  if (axis == "Y") {
    x = 1, y = -1;
  }
  std::vector<float> vecRotated(6);
  vecRotated[5] = vec[5];
  vecRotated[4] = vec[4];
  vecRotated[3] = vec[3];
  vecRotated[0] = y * vec[0];
  vecRotated[1] = x * vec[1];
  vecRotated[2] = vec[2];
  return vecRotated;
}


void
graph::draw()
{
    glBindVertexArray(render.VAO);
    glLineWidth(1.3f);
    glDrawArrays(GL_LINES, 0, gridVertices.size()/6);
}
