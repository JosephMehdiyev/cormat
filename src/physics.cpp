#include "physics.hpp"
#include "objects.hpp"

void physics::update(object &object, float deltaT)
{
    if (object.type == bodyType::DYNAMIC)
    {
        updateVelocity(object, deltaT);
        updatePosition(object, deltaT);
    }
}

void physics::updateVelocity(object &object, float deltaT)
{
    if (object.type == bodyType::DYNAMIC)
        object.velocity += object.acceleration * deltaT;
}

void physics::updatePosition(object &object, float deltaT)
{
    if (object.type == bodyType::DYNAMIC)

        object.position += object.velocity * deltaT;
}
