#include "render.hpp"
#include "glad.h"
#include "shader.hpp"
#include "texture.hpp"
#include <GL/gl.h>

render::render() : shader("../shader/graph.vert.glsl", "../shader/graph.frag.glsl")
{
    entities.push_back(std::make_unique<sphere>());
    entities.push_back(std::make_unique<rectangle>(0.5f, 0.5f, "FLOOR"));
    entities.push_back(std::make_unique<sphere>());
    entities[2]->setPosition({0.0f, 21.0f, 0.0f});
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

    for (auto &x : entities)
    {
        x->draw(camera, shader);
        if (isCollisionMode)
            x->getCollision()->draw(camera, shader);
    }
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
