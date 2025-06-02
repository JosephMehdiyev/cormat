#include "physics.hpp"

void physics::update(object &sphere, float deltaT)
{
    updateVelocity(sphere, deltaT);
    updatePosition(sphere, deltaT);
}

void physics::updateVelocity(object &object, float deltaT)
{
    object.velocity += object.acceleration * deltaT;
}

void physics::updatePosition(object &object, float deltaT)
{
    object.position += object.velocity * deltaT;
}
