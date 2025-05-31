#include "graph.hpp"
#include "glad.h"
#include <GL/gl.h>
#include <vector>

graph::graph() : shader("../shader/graph.vert.glsl", "../shader/graph.frag.glsl")
{
    cube test;
    render.setBuffer(test);
}

void graph::draw()
{
    glBindVertexArray(render.VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void graph::start(camera camera)
{

    graph::setRenderingConfig();
    shader.use();
    graph::initializeAndUpdateShaders(camera);
    graph::draw();
}

void graph::initializeAndUpdateShaders(camera camera)
{
    shader.updateProjectionM(camera.fov);
    shader.updateViewM(camera.cameraPosition, camera.cameraFront, camera.worldUp);
    shader.updateModelM(camera.changeInX, camera.changeInY, camera.cameraRotationSpeed);
}

void graph::setRenderingConfig()
{
    glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
