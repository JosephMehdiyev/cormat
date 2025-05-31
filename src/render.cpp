#include "render.hpp"
#include "glad.h"
#include <GL/gl.h>
#include <vector>

render::render() : shader("../shader/graph.vert.glsl", "../shader/graph.frag.glsl")
{
    cube test;
    buffer.setBuffer(test);
}

void render::draw()
{
    glBindVertexArray(buffer.VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void render::start(camera camera)
{

    render::setRenderingConfig();
    shader.use();
    render::initializeAndUpdateShaders(camera);
    render::draw();
}

void render::initializeAndUpdateShaders(camera camera)
{
    shader.updateProjectionM(camera.fov);
    shader.updateViewM(camera.cameraPosition, camera.cameraFront, camera.worldUp);
    shader.updateModelM(camera.changeInX, camera.changeInY, camera.cameraRotationSpeed);
}

void render::setRenderingConfig()
{
    glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
