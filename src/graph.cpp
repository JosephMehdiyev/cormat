#include "graph.hpp"
#include "glad.h"
#include <GL/gl.h>
#include <vector>

graph::graph(int numberOfBoxes) : shader("../shader/graph.vert.glsl", "../shader/graph.frag.glsl")
{
    totalBoxes = numberOfBoxes;
    // NOTE: each vector represents a vertices with its 6 float data.
    //      first 3 floats represent the position in normal coordinates.
    //      later 3 floats represent the color of the vertice.
    //      2 vertices are in the group to draw a line.
    gridVertices  = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
                    -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,

                    0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
                    0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

                    0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
                    0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f};
    n = 0;
   // for (int i = 0; i < totalBoxes + 1; i++)
   // {
   //     std::vector<float> vec(6);
   //     std::vector<float> vec2(6);

   //     vec[0] = -10.0f + 10.0* static_cast<float>(i) / totalBoxes * 2.0f;
   //     vec[1] = +10.0f;
   //     vec[2] = 0.0f;
   //     vec[3] = 0.0;
   //     vec[4] = 0.0;
   //     vec[5] = 0.0;
   //     vec2 = findPairSymmetry(vec, "X");

   //     for (unsigned int j = 0; j < 6; j++) gridVertices.push_back(vec[j]);
   //     for (unsigned int j = 0; j < 6 ; j++) gridVertices.push_back(vec2[j]);
   // }

   // for (int i = 0; i < totalBoxes + 1; i++)
   // {
   //     std::vector<float> vec(6);
   //     std::vector<float> vec2(6);

   //     vec[0] = -10.0f ;
   //     vec[1] = +10.0f - 10.0* static_cast<float>(i) / totalBoxes * 2.0f;
   //     vec[2] = 0.0f;
   //     vec[3] = 0.0;
   //     vec[4] = 0.0;
   //     vec[5] = 0.0;
   //     vec2 = findPairSymmetry(vec, "Y");

   //     for (unsigned int j = 0; j < 6; j++) gridVertices.push_back(vec[j]);
   //     for (unsigned int j = 0; j < 6; j++) gridVertices.push_back(vec2[j]);
   // }
    pointGenerator();
    render.setBuffer(gridVertices);


}


std::vector<float> graph::findPairSymmetry(std::vector<float> vec, std::string axis) 
{
    int x, y;
    if (axis == "X") x = -1, y = 1;
    if (axis == "Y") x = 1, y = -1;
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
    int x = gridVertices.size()/6;
    glBindVertexArray(render.VAO);
    glLineWidth(1.3f);
    glPointSize(3.0f);
    glDrawArrays(GL_LINES, 0, x-n);
    glDrawArrays(GL_POINTS, x-n,  n);
}


void
graph::start(glfwCamera glfwCamera)
{

    graph::setRenderingConfig();
    shader.use();
    graph::initializeAndUpdateShaders(glfwCamera);
    graph::draw();
}


void
graph::initializeAndUpdateShaders(glfwCamera glfwCamera)
{
    shader.updateProjectionM(glfwCamera.fov);
    shader.updateViewM(glfwCamera.cameraPosition, glfwCamera.cameraFront, glfwCamera.worldUp);
    shader.updateModelM(glfwCamera.changeInX, glfwCamera.changeInY);
}


void
graph::setRenderingConfig()
{
    glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


// NOTE: Z axis is the line that comes through the screen to the real world, it is not "up" axis.
// "up" axis is the Y axis, hence the function must be sent to the y corresponding index of our vector.
void
graph::pointGenerator()
{
    for(float i = -10.0; i < 10; i += 0.1)
    {
        for(float j = -10.0; j < 10; j += 0.11)
        {
            gridVertices.push_back(i);
            gridVertices.push_back(pow(i, 2) + pow(j, 2));
            gridVertices.push_back(j); 
            gridVertices.push_back(1.0);
            gridVertices.push_back(0.0);
            gridVertices.push_back(0.0);
            n++; // counts the number of parabole vertices
        }
    }
}
