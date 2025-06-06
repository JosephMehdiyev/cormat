#include "entity.hpp"
#include "collision.hpp"
#include "collisionBox.hpp"
#include <memory>

entity::entity() {};
entity::~entity()
{
}

bool entity::isStatic()
{
    if (bodyType == BODY_TYPE::STATIC)
        return true;
    else
        return false;
}

bool entity::isDynamic()
{
    return !isStatic();
}

collisionBox *entity::getCollisionBox()
{
    return collisionBox ? collisionBox.get() : nullptr;
}
COLLISION_TYPE &entity::getCollisionType()
{
    return collisionType;
}

BODY_TYPE &entity::getBodyType()
{
    return bodyType;
}

glm::vec3 &entity::getVelocity()
{
    return velocity;
}

glm::vec3 &entity::getAcceleration()
{
    return acceleration;
}

float entity::getMass()
{
    return mass;
}

void entity::setCollisionBox(std::unique_ptr<class collisionBox> data)
{
    collisionBox = std::move(data);
}
void entity::setCollisionType(const COLLISION_TYPE &data)
{
    collisionType = data;
}

void entity::setBodyType(const BODY_TYPE &data)
{
    bodyType = data;
}

void entity::setVelocity(const glm::vec3 &data)
{
    velocity = data;
}

void entity::setAcceleration(const glm::vec3 &data)
{
    acceleration = data;
}

void entity::setMass(const float &data)
{
    mass = data;
}
