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
    gridVertices = {1.0f, 0.0f,  0.0f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
                    0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,  0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f};
    n = 0;
    render.setBuffer(gridVertices);
}

std::vector<float> graph::findPairSymmetry(std::vector<float> vec, std::string axis)
{
    int x, y;
    if (axis == "X")
        x = -1, y = 1;
    if (axis == "Y")
        x = 1, y = -1;
    std::vector<float> vecRotated(6);
    vecRotated[5] = vec[5];
    vecRotated[4] = vec[4];
    vecRotated[3] = vec[3];
    vecRotated[0] = y * vec[0];
    vecRotated[1] = x * vec[1];
    vecRotated[2] = vec[2];
    return vecRotated;
}

void graph::draw()
{
    int x = gridVertices.size() / 6;
    glBindVertexArray(render.VAO);
    glLineWidth(1.3f);
    glPointSize(3.0f);
    glDrawArrays(GL_LINES, 0, x - n);
    glDrawArrays(GL_POINTS, x - n, n);
}

void graph::start(glfwCamera glfwCamera)
{

    graph::setRenderingConfig();
    shader.use();
    graph::initializeAndUpdateShaders(glfwCamera);
    graph::draw();
}

void graph::initializeAndUpdateShaders(glfwCamera glfwCamera)
{
    shader.updateProjectionM(glfwCamera.fov);
    shader.updateViewM(glfwCamera.cameraPosition, glfwCamera.cameraFront, glfwCamera.worldUp);
    shader.updateModelM(glfwCamera.changeInX, glfwCamera.changeInY, glfwCamera.cameraRotationSpeed);
}

void graph::setRenderingConfig()
{
    glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

// NOTE: Z axis is the line that comes through the screen to the real world, it is not "up" axis.
// "up" axis is the Y axis, hence the function must be sent to the y corresponding index of our vector.
// i and j are equivalent to x and y.
void graph::pointGenerator()
{
    for (float i = -10; i < 10; i += 0.1)
    {
        for (float j = -10; j < 10;
             j += 0.1) // NOTE: you may change the intervals i and j goes through, it will change the size of the graph.
                       // You may also change the addition value (here for example 0.1), it will change the density of the points of the graph.
        {
            gridVertices.push_back(i);
            gridVertices.push_back(sin(i) + cos(j)); // NOTE: change the functon here, i and j are equivalent to x and y.
            gridVertices.push_back(j);
            gridVertices.push_back(1.0);
            gridVertices.push_back(0.0);
            gridVertices.push_back(0.0);
            n++; // counts the number of function vertices
                 // NOTE: it tracks number of ALL the function vertices, not just one.
                 // if this function is called once, n is just a local counter, otherwise it is global.
        }
    }
}
