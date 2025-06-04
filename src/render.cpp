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
    if (collision::isCollidingSphereAABB(floor, particle))
        particle.velocity.y = -particle.velocity.y;
    floor.draw(camera, shader);
    if (isCollisionMode)
        floor.collision->draw(particle, camera, shader);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINES);
    particle.draw(camera, shader);
    if (isCollisionMode)
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
