#include "render.hpp"
#include "glad.h"
#include "shader.hpp"
#include "texture.hpp"
#include <GL/gl.h>

render::render() : shader("../shader/graph.vert.glsl", "../shader/graph.frag.glsl")
{
    floor.setBuffer();
    floor.collision->setBuffer();
    particle.setBuffer();
    particle.collision->setBuffer();
}

void render::start(camera camera, float deltaT)
{

    render::setRenderingConfig();
    shader.use();
    render::initializeAndUpdateMatrices(camera);
    physics::update(particle, deltaT);
    floor.draw(camera, shader);
    floor.collision->draw(particle, camera, shader);
    particle.draw(camera, shader);
    particle.collision->draw(particle, camera, shader);
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
