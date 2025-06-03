#include "physics.hpp"

void physics::update(entity &object, float deltaT)
{
    if (object.type == bodyType::DYNAMIC)
    {
        updateVelocity(object, deltaT);
        updatePosition(object, deltaT);
    }
}

void physics::updateVelocity(entity &object, float deltaT)
{
    if (object.type == bodyType::DYNAMIC)
        object.velocity += object.acceleration * deltaT;
}

void physics::updatePosition(entity &object, float deltaT)
{
    if (object.type == bodyType::DYNAMIC)

        object.position += object.velocity * deltaT;
}
