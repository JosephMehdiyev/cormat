#include "collision.hpp"
#include "collisionBox.hpp"
#include "entity.hpp"
#include "rectangle.hpp"
#include "sphere.hpp"
#include <cmath>
#include <glm/geometric.hpp>

bool collision::isCollidingSphereAABB(sphere &sphere, entity &AABB)
{
    glm::vec3 closestPoint =
        glm::clamp(sphere.getPosition(), AABB.getCollisionBox()->getMin(), AABB.getCollisionBox()->getMax());
    glm::vec3 difference = sphere.getPosition() - closestPoint;
    float differenceLength = glm::length(difference);
    // if they collide, do static collision handler so they are not inside each other
    if (differenceLength < sphere.getRadius())
    {
        if (differenceLength == 0)
            return true;
        glm::vec3 normal = glm::normalize(difference);
        if (sphere.isDynamic() && AABB.isStatic())
            sphere.getPosition() += normal * (sphere.getRadius() - differenceLength);
        else if (sphere.isStatic() && AABB.isDynamic())
        {
            float penet = sphere.getRadius() - differenceLength;
            glm::vec3 res = normal * penet;
            AABB.getCollisionBox()->getMin() -= res;
            AABB.getCollisionBox()->getMax() -= res;
        }
        else if (sphere.isDynamic() && AABB.isDynamic())
        {
            float penet = sphere.getRadius() - differenceLength;
            glm::vec3 res = normal * (penet / 2);
            AABB.getCollisionBox()->getMin() -= res;
            AABB.getCollisionBox()->getMax() -= res;
            sphere.getPosition() += res;
        }
        return true;
    }
    return false;
}

// FIXME:: Optimize this, it checks the NaN case for normals so bad optimization
bool collision::isCollidingSphereSphere(sphere &sphere1, sphere &sphere2)
{
    const float distance = glm::length(sphere1.getPosition() - sphere2.getPosition());

    // If they collide, do static collision handler so they are not inside each other
    if (distance < sphere1.getRadius() + sphere2.getRadius())
    {
        glm::vec3 distanceVector = sphere1.getPosition() - sphere2.getPosition();
        if (distanceVector == glm::vec3(0.0f))
            distanceVector = (sphere1.getPosition() * 1.01f) - sphere2.getPosition();
        const float moveDistance = (sphere1.getRadius() + sphere2.getRadius() - distance) / 2;
        if (sphere1.isDynamic() && sphere2.isDynamic())
        {
            sphere1.getPosition() += glm::normalize(distanceVector) * moveDistance;
            sphere2.getPosition() -= glm::normalize(distanceVector) * moveDistance;
        }
        else if (sphere1.isStatic() && sphere2.isDynamic())
            sphere2.getPosition() -= glm::normalize(distanceVector) * (moveDistance * 2);
        else if (sphere1.isDynamic() && sphere2.isStatic())
            sphere1.getPosition() -= glm::normalize(distanceVector) * (moveDistance * 2);
        return true;
    }
    return false;
}

bool collision::isCollidingAABBAABB(entity &a, entity &b)
{
    return (a.getCollisionBox()->getMin().x <= b.getCollisionBox()->getMax().x &&
            a.getCollisionBox()->getMax().x >= b.getCollisionBox()->getMin().x) &&
           (a.getCollisionBox()->getMin().y <= b.getCollisionBox()->getMax().y &&
            a.getCollisionBox()->getMax().y >= b.getCollisionBox()->getMin().y) &&
           (a.getCollisionBox()->getMin().z <= b.getCollisionBox()->getMax().z &&
            a.getCollisionBox()->getMax().z >= b.getCollisionBox()->getMin().z);
}

bool collision::checkCollisions(entity &first, entity &second)
{
    if (first.isSphere() && second.isSphere())
        return collision::isCollidingSphereSphere(dynamic_cast<sphere &>(first), dynamic_cast<sphere &>(second));
    else if (first.isSphere() && second.isAABB())
        return collision::isCollidingSphereAABB(dynamic_cast<sphere &>(first), second);
    else if (first.isAABB() && second.isSphere())
        return collision::isCollidingSphereAABB(dynamic_cast<sphere &>(second), first);
    else if (first.isAABB() && second.isAABB())
        return collision::isCollidingAABBAABB(first, second);
    else
        return false;
}

// naive implementation
void collision::handleCollisions(entity &first, entity &second)
{
    glm::vec3 normal;
    if (first.isAABB() && second.isSphere())
        normal =
            glm::normalize(second.getPosition() - glm::clamp(second.getPosition(), first.getCollisionBox()->getMin(),
                                                             first.getCollisionBox()->getMax()));
    else if (first.isSphere() && second.isAABB())
        normal =
            glm::normalize(first.getPosition() - glm::clamp(first.getPosition(), second.getCollisionBox()->getMin(),
                                                            second.getCollisionBox()->getMax()));

    else
        normal = glm::normalize(second.getPosition() - first.getPosition());
    float velNormal1 = glm::dot(first.getVelocity(), normal);
    float velNormal2 = glm::dot(second.getVelocity(), normal);
    float j = -1.8f * (velNormal1 - velNormal2);

    if (!first.isStatic() && !second.isStatic())
    {
        j /= 2;
        glm::vec3 impulse = j * normal;
        first.getVelocity() += impulse;
        second.getVelocity() -= impulse;
    }
    else if (first.isStatic() && !second.isStatic())
    {
        second.getVelocity() -= (j * normal);
    }
    else if (!first.isStatic() && second.isStatic())
        first.getVelocity() += (j * normal);
}
