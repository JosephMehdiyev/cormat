#include "collision.hpp"
#include "entity.hpp"
#include "sphere.hpp"

collision::collision(const entity &entity)
{
    min = entity.min;
    max = entity.max;
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

bool collision::isPointInsideSphere(const glm::vec3 &point, const sphere &sphere)
{
    const float distance = sqrt(pow((point.x - sphere.position.x), 2) + pow((point.y - sphere.position.y), 2) +
                                pow((point.z - sphere.position.z), 2));
    return distance < sphere.radius;
}

bool collision::isCollidingSphereAABB(const entity &AABB, const sphere &sphere)
{
    const float x = std::max(AABB.min.x, std::min(sphere.position.x, AABB.max.x));
    const float y = std::max(AABB.min.y, std::min(sphere.position.y, AABB.max.y));
    const float z = std::max(AABB.min.z, std::min(sphere.position.z, AABB.max.z));
    const glm::vec3 point = {x, y, z};
    return collision::isPointInsideSphere(point, sphere);
}

bool collision::isCollidingSphereSphere(const sphere &sphere1, const sphere &sphere2)
{
    const float distance =
        sqrt(pow((sphere1.position.x - sphere2.position.x), 2) + pow((sphere1.position.y - sphere2.position.y), 2) +
             pow((sphere1.position.z - sphere2.position.z), 2));

    return distance < sphere1.radius + sphere2.radius;
}
