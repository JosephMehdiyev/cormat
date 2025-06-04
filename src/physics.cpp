#include "physics.hpp"

void physics::update(std::vector<std::unique_ptr<entity>> &entities, float deltaT)
{
    for (auto &object : entities)
    {
        if (object->getBodyType() == BODY_TYPE::DYNAMIC)
        {
            updateVelocity(object, deltaT);
            updatePosition(object, deltaT);
        }
    }
    for (unsigned int i = 0; i < entities.size(); ++i)
    {
        for (unsigned int j = i + 1; j < entities.size(); ++j)
        {
            if (collision::checkCollisions(*entities[i], *entities[j]))
            {
                collision::handleCollisions(*entities[i], *entities[j]);
            }
        }
    }
}

void physics::updateVelocity(std::unique_ptr<entity> &object, float deltaT)
{
    if (object->getBodyType() == BODY_TYPE::DYNAMIC)
        object->setVelocity(object->getVelocity() + object->getAcceleration() * deltaT);
}

void physics::updatePosition(std::unique_ptr<entity> &object, float deltaT)
{
    if (object->getBodyType() == BODY_TYPE::DYNAMIC)

        object->setPosition(object->getPosition() + object->getVelocity() * deltaT);
}
