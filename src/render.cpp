#include "render.hpp"
#include "glad.h"
#include "shader.hpp"
#include "texture.hpp"
#include <GL/gl.h>

render::render() : shader("../shader/graph.vert.glsl", "../shader/graph.frag.glsl")
{
    entities.push_back(std::make_unique<sphere>());
    entities.push_back(std::make_unique<rectangle>(0.5f, 0.5f, "FLOOR"));
    for (auto &x : entities)
    {
        x->setBuffer();
        x->getCollision()->setBuffer();
    }
}

void render::start(camera camera, float deltaT)
{

    render::setRenderingConfig();
    shader.use();
    render::initializeAndUpdateMatrices(camera);
    physics::update(entities, deltaT);
    entities[1]->draw(camera, shader);
    if (isCollisionMode)
        entities[1]->getCollision()->draw(camera, shader);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINES);
    entities[0]->draw(camera, shader);
    if (isCollisionMode)
        entities[0]->getCollision()->draw(camera, shader);
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
