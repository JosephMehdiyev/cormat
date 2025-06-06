#include "render.hpp"
#include "collisionBox.hpp"
#include "entity.hpp"
#include "glad.h"
#include "shader.hpp"
#include "texture.hpp"
#include <GL/gl.h>
#include <random>

float randomFloat()
{
    std::random_device rd;  // Seed
    std::mt19937 gen(rd()); // Mersenne Twister engine
    std::uniform_real_distribution<float> dist(0.0f, 5.0f);

    return dist(gen);
}

render::render() : shader("../shader/graph.vert.glsl", "../shader/graph.frag.glsl")
{
    entities.push_back(std::make_unique<rectangle>(0.5f, 0.5f));
    // entities.push_back(std::make_unique<rectangle>(0.5f, 0.5f));
    // entities.push_back(std::make_unique<rectangle>(0.5f, 0.5f));
    // entities.push_back(std::make_unique<rectangle>(0.5f, 0.5f));
    // entities.push_back(std::make_unique<rectangle>(0.5f, 0.5f));
    // entities[1]->setRotation({0.0, 0.0, 0.0});
    // entities[1]->setPosition({0.0, 0.25, 0.25});

    // entities[2]->setRotation({0.0, 0.0, 0.0});
    // entities[2]->setPosition({0.0, 0.25, -0.25});

    // entities[3]->setRotation({0.0, -90.0, 0.0});
    // entities[3]->setPosition({0.0, 0.25, 0.25});

    // entities[4]->setRotation({0.0, 90.0, 0.0});
    // entities[4]->setPosition({0.0, 0.25, 0.25});

    for (int i = 0; i < 300; i++)
    {
        entities.push_back(std::make_unique<sphere>());
        entities[i + 1]->setPosition({randomFloat(), 15.0f + randomFloat(), randomFloat()});
        entities[i + 1]->setVelocity({randomFloat() * 2, 10.0f + randomFloat(), randomFloat() * 2});
    }

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
    if (startUpdatingPhysics)
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
