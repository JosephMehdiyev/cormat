#include "render.hpp"
#include "glad.h"
#include "shader.hpp"
#include <GL/gl.h>

render::render() : shader("../shader/graph.vert.glsl", "../shader/graph.frag.glsl")
{
    test1.setBuffer(test1.coordData, test1.indiceData);
    test.setBuffer(test.coordData, test.indiceData);
}

void render::start(camera camera)
{

    render::setRenderingConfig();
    shader.use();
    render::initializeAndUpdateShaders(camera);
    glBindVertexArray(test1.VAO);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    test.modelMatrix = glm::mat4(1.0f);
    shader.updateModelM(camera.changeInX, camera.changeInY, camera.cameraRotationSpeed, test);
    test.draw();
    test1.modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 2.0f, -2.0f));
    shader.updateModelM(camera.changeInX, camera.changeInY, camera.cameraRotationSpeed, test1);
    test1.draw();
}

void render::initializeAndUpdateShaders(camera camera)
{
    shader.updateProjectionM(camera.fov);
    shader.updateViewM(camera.cameraPosition, camera.cameraFront, camera.worldUp);
    shader.updateModelM(camera.changeInX, camera.changeInY, camera.cameraRotationSpeed, test1);
}

void render::setRenderingConfig()
{
    glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
