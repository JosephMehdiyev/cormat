#include "render.hpp"
#include "glad.h"
#include "shader.hpp"
#include <GL/gl.h>

render::render() : shader("../shader/graph.vert.glsl", "../shader/graph.frag.glsl")
{
    test.setBuffer(test1.coordData, test1.indiceData);
}

void render::start(camera camera)
{

    render::setRenderingConfig();
    shader.use();
    render::initializeAndUpdateMatrices(camera);

    test.modelMatrix = glm::mat4(1.0f);
    test.modelMatrix = glm ::scale(test.modelMatrix, glm::vec3(20.0f));
    test.modelMatrix = glm::rotate(test.modelMatrix, static_cast<float>(glm::radians(90.0f)), glm::vec3(1.0f, 0.0f, 0.0f));

    test.updateModelMatrix(camera, shader);
    test.draw();
}

void render::initializeAndUpdateMatrices(camera camera)
{
    shader.updateProjectionM(camera.fov);
    shader.updateViewM(camera.cameraPosition, camera.cameraFront, camera.worldUp);
}

void render::setRenderingConfig()
{
    glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
