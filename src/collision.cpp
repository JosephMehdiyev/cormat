#include "collision.hpp"
#include "entity.hpp"
#include "sphere.hpp"
#include <glm/geometric.hpp>

collision::collision(entity &entity)
{
    min = entity.getMin();
    max = entity.getMax();
    verticeData = getVerticeData(min, max);
    indiceData = {0, 1, 1, 3, 3, 2, 2, 0, 4, 5, 5, 7, 7, 6, 6, 4, 0, 4, 1, 5, 2, 6, 3, 7};
}

// FIXME: must ignore rotations
void collision::draw(camera camera, shader shader)
{
    glBindVertexArray(VAO);
    shader.setBool("useTexture", false);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawElements(GL_LINES, indiceData.size(), GL_UNSIGNED_INT, 0);
}

void collision::setBuffer()
{
    if (verticeData.empty())
        throw std::invalid_argument("Vertice Data Cannot be Empty");
    if (indiceData.empty())
        throw std::invalid_argument("Indice Data Cannot be Empty");
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, static_cast<long long int>(sizeof(float) * verticeData.size()), &verticeData[0],
                 GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<long long int>(sizeof(unsigned int) * indiceData.size()),
                 &indiceData[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void *>(0));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void *>(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    unsigned int err = glGetError();
    if (err != GL_NO_ERROR)
    {
        throw std::runtime_error("Failed to set Vertice or Indice Data to Buffers: " + std::to_string(err));
    }
}

std::vector<float> collision::getVerticeData(glm::vec3 min, glm::vec3 max)
{
    return {min.x, min.y, min.z, RED, max.x, min.y, min.z, RED, min.x, max.y, min.z, RED, max.x, max.y, min.z, RED,
            min.x, min.y, max.z, RED, max.x, min.y, max.z, RED, min.x, max.y, max.z, RED, max.x, max.y, max.z, RED};
}

bool collision::isCollidingSphereAABB(sphere &sphere, entity &AABB)
{
    glm::vec3 closestPoint = glm::clamp(sphere.getPosition(), AABB.getCollision()->min, AABB.getCollision()->max);
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
        else if (sphere.isDynamic() && AABB.isDynamic())
        {
            float penet = sphere.getRadius() - differenceLength;
            glm::vec3 res = normal * (penet / 2);
            AABB.getMin() -= res;
            AABB.getMax() -= res;
            sphere.getPosition() += res;
        }
        return true;
    }
    return false;
}

bool collision::isCollidingSphereSphere(sphere &sphere1, sphere &sphere2)
{
    const float distance = glm::length(sphere1.getPosition() - sphere2.getPosition());

    // If they collide, do static collision handler so they are not inside each other
    if (distance < sphere1.getRadius() + sphere2.getRadius())
    {
        const glm::vec3 distanceVector = sphere1.getPosition() - sphere2.getPosition();
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
    return (a.getMin().x <= b.getMax().x && a.getMax().x >= b.getMin().x) &&
           (a.getMin().y <= b.getMax().y && a.getMax().y >= b.getMin().y) &&
           (a.getMin().z <= b.getMax().z && a.getMax().z >= b.getMin().z);
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

void collision::handleCollisions(entity &first, entity &second)
{
    if (first.getBodyType() == BODY_TYPE::DYNAMIC)
    {
        first.getVelocity().y *= -0.5;
    }

    if (second.getBodyType() == BODY_TYPE::DYNAMIC)
    {
        second.getVelocity().y *= -0.5;
    }
}
