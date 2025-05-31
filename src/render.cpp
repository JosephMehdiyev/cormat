#include "render.hpp"
#include "glad.h"
#include "shader.hpp"
#include <GL/gl.h>

render::render() : shader("../shader/graph.vert.glsl", "../shader/graph.frag.glsl")
{
    buffer.setBuffer(test);
}

void render::draw()
{
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void render::start(camera camera)
{

    render::setRenderingConfig();
    shader.use();
    render::initializeAndUpdateShaders(camera);
    glBindVertexArray(buffer.VAO);
    // identity or your desired transform
    render::draw();
    test.modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 5.0f, -5.0f));
    shader.setMat4("model", test.modelMatrix);
    render::draw();
}

void render::initializeAndUpdateShaders(camera camera)
{
    shader.updateProjectionM(camera.fov);
    shader.updateViewM(camera.cameraPosition, camera.cameraFront, camera.worldUp);
    shader.updateModelM(camera.changeInX, camera.changeInY, camera.cameraRotationSpeed, test);
}

void render::setRenderingConfig()
{
    glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
