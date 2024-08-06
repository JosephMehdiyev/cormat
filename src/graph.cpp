#include "graph.hpp"
#include "glm/glm.hpp"
#include "glad.h"
#include <GL/gl.h>
#include <vector>

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

  render.setBuffer(gridVertices);
}


void
graph::draw()
{
    glBindVertexArray(render.VAO);
    glLineWidth(1.3f);
    glDrawArrays(GL_LINES, 0, 6);
}
