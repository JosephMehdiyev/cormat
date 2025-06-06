#include "render.hpp"
#include "collisionBox.hpp"
#include "entity.hpp"
#include "glad.h"
#include "shader.hpp"
#include "texture.hpp"
#include <GL/gl.h>

render::render() : shader("../shader/graph.vert.glsl", "../shader/graph.frag.glsl")
{
    entities.push_back(std::make_unique<rectangle>(0.5f, 0.5f));
    entities.push_back(std::make_unique<sphere>());
    entities.push_back(std::make_unique<sphere>());
    for (auto &x : entities)
    {
        x->setBuffer();
        if (x->getCollisionBox() != nullptr)
            x->getCollisionBox()->setBuffer();
    }
}

void render::start(camera camera, float deltaT)
{

    render::setRenderingConfig();
    shader.use();
    render::initializeAndUpdateMatrices(camera);
    physics::update(entities, deltaT);

    // FIXME: if collisionBox is not draw after its base entity, it will cause issues
    for (auto &x : entities)
    {
        x->draw(camera, shader);
        if (isCollisionMode)
            if (x->getCollisionBox() != nullptr)
                x->getCollisionBox()->draw(camera, shader);
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
