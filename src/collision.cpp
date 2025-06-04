#include "collision.hpp"
#include "entity.hpp"
#include "sphere.hpp"

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

bool collision::isPointInsideSphere(glm::vec3 &point, sphere &sphere)
{
    const float distance =
        sqrt(pow((point.x - sphere.getPosition().x), 2) + pow((point.y - sphere.getPosition().y), 2) +
             pow((point.z - sphere.getPosition().z), 2));
    return distance < sphere.radius;
}

bool collision::isCollidingSphereAABB(sphere &sphere, entity &AABB)
{
    float x = std::max(AABB.getMin().x, std::min(sphere.getPosition().x, AABB.getMax().x));
    float y = std::max(AABB.getMin().y, std::min(sphere.getPosition().y, AABB.getMax().y));
    float z = std::max(AABB.getMin().z, std::min(sphere.getPosition().z, AABB.getMax().z));
    glm::vec3 point = {x, y, z};
    return collision::isPointInsideSphere(point, sphere);
}

bool collision::isCollidingSphereSphere(sphere &sphere1, sphere &sphere2)
{
    const float distance = sqrt(pow((sphere1.getPosition().x - sphere2.getPosition().x), 2) +
                                pow((sphere1.getPosition().y - sphere2.getPosition().y), 2) +
                                pow((sphere1.getPosition().z - sphere2.getPosition().z), 2));

    return distance < sphere1.radius + sphere2.radius;
}

bool collision::isCollidingAABBAABB(entity &a, entity &b)
{
    return (a.getMin().x <= b.getMax().x && a.getMax().x >= b.getMin().x) &&
           (a.getMin().y <= b.getMax().y && a.getMax().y >= b.getMin().y) &&
           (a.getMin().z <= b.getMax().z && a.getMax().z >= b.getMin().z);
}

bool collision::checkCollisions(entity &first, entity &second)
{
}
