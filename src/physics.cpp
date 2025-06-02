#include "physics.hpp"

void physics::update(object &object, float deltaT)
{
    updateVelocity(object, deltaT);
    updatePosition(object, deltaT);
}

void physics::updateVelocity(object &object, float deltaT)
{
    object.velocity += object.acceleration * deltaT;
}

void physics::updatePosition(object &object, float deltaT)
{
    object.position += object.velocity * deltaT;
}
