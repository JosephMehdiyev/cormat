#include "collisionBox.hpp"
#include "rectangle.hpp"
#include "sphere.hpp"
#include <glm/gtc/quaternion.hpp>

collisionBox::collisionBox(entity &entity)
{
    setHasTexture(false);
    initializeMinMax(entity);
    setVerticeData(generateVerticeData(min, max));
    setIndiceData({0, 1, 1, 3, 3, 2, 2, 0, 4, 5, 5, 7, 7, 6, 6, 4, 0, 4, 1, 5, 2, 6, 3, 7});
    glm::vec3 rad = glm::radians(entity.getRotation());
    glm::quat rotate = glm::quat(rad);
    // FIXME:: min\max should be updated regularly
    min = (rotate * min) * entity.getScale();
    max = (rotate * max) * entity.getScale();
}

void collisionBox::draw(camera &camera, shader &shader)
{
    glBindVertexArray(getVAO());
    shader.setBool("useTexture", false);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawElements(GL_LINES, getIndiceData().size(), GL_UNSIGNED_INT, 0);
}

void collisionBox::initializeMinMax(entity &entity)
{
    if (entity.isSphere())
    {
        auto *sphr = dynamic_cast<sphere *>(&entity);
        min = -glm::vec3(sphr->getRadius());
        max = glm::vec3(sphr->getRadius());
    }
    else if (entity.isAABB())
    {
        auto *rect = dynamic_cast<rectangle *>(&entity);
        min = {-rect->getWidth(), -rect->getHeight(), -rect->getThickness()};
        max = {rect->getWidth(), rect->getHeight(), rect->getThickness()};
    }
}

void collisionBox::updateMinMax(entity &entity)
{
    if (entity.isAABB())
    {
        glm::mat4 modelMatrix = glm::mat4(1.0f);
        modelMatrix = glm::rotate(modelMatrix, glm::radians(getRotation().x), glm::vec3(1.0f, 0.0f, 0.0f)); // X-axis
        modelMatrix = glm::rotate(modelMatrix, glm::radians(getRotation().y), glm::vec3(0.0f, 1.0f, 0.0f)); // Y-axis
        modelMatrix = glm::rotate(modelMatrix, glm::radians(getRotation().z), glm::vec3(0.0f, 0.0f, 1.0f)); // Z-axis
        modelMatrix = glm::scale(modelMatrix, getScale());
        min = modelMatrix * glm::vec4(min, 1.0f);
        max = modelMatrix * glm::vec4(min, 1.0f);
    }
}

std::vector<float> collisionBox::generateVerticeData(glm::vec3 min, glm::vec3 max)
{
    return {min.x, min.y, min.z, RED, max.x, min.y, min.z, RED, min.x, max.y, min.z, RED, max.x, max.y, min.z, RED,
            min.x, min.y, max.z, RED, max.x, min.y, max.z, RED, min.x, max.y, max.z, RED, max.x, max.y, max.z, RED};
}

glm::vec3 &collisionBox::getMin()
{
    return min;
};

glm::vec3 &collisionBox::getMax()
{
    return max;
};
