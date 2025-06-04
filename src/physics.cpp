#include "physics.hpp"

void physics::update(std::vector<std::unique_ptr<entity>> &entities, float deltaT)
{
    for (auto &object : entities)
    {
        if (object->type == bodyType::DYNAMIC)
        {
            updateVelocity(object, deltaT);
            updatePosition(object, deltaT);
        }
    }
}

void physics::updateVelocity(std::unique_ptr<entity> &object, float deltaT)
{
    if (object->type == bodyType::DYNAMIC)
        object->velocity += object->acceleration * deltaT;
}

void physics::updatePosition(std::unique_ptr<entity> &object, float deltaT)
{
    if (object->type == bodyType::DYNAMIC)

        object->position += object->velocity * deltaT;
}
