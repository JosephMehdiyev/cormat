#include "entity.hpp"
#include <memory>

entity::entity() {};

void entity::draw(const camera &camera, const shader &shader)
{
    updateModelMatrix(camera, shader);
    glBindVertexArray(VAO);
    if (hasTexture)
        shader.setBool("useTexture", true);
    else
        shader.setBool("useTexture", false);
    if (isPolygonMode)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDrawElements(GL_TRIANGLES, indiceData.size(), GL_UNSIGNED_INT, 0);
};

void entity::updateModelMatrix(camera camera, shader shader)
{
    // modelMatrix = glm::rotate(modelMatrix, static_cast<float>(glm::radians(camera.changeInX)), glm::vec3(0.0f, 1.0f,
    // 0.0f)); modelMatrix = glm::rotate(modelMatrix, static_cast<float>(glfwGetTime() * camera.cameraRotationSpeed),
    // glm::vec3(0.0f, 1.0f, 0.0f)); modelMatrix = glm::rotate(modelMatrix,
    // static_cast<float>(glm::radians(camera.changeInY)), glm::vec3(1.0f, 0.0f, 0.0f));
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, position);
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)); // X-axis
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)); // Y-axis
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f)); // Z-axis
    modelMatrix = glm::scale(modelMatrix, scale);

    glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgramID, "model"), 1, GL_FALSE, &modelMatrix[0][0]);
}

void entity::setBuffer()
{
    if (coordData.empty())
        throw std::invalid_argument("Vertice Data Cannot be Empty");
    if (indiceData.empty())
        throw std::invalid_argument("Indice Data Cannot be Empty");
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, static_cast<long long int>(sizeof(float) * coordData.size()), &coordData[0],
                 GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<long long int>(sizeof(unsigned int) * indiceData.size()),
                 &indiceData[0], GL_STATIC_DRAW);
    if (!hasTexture)
    {

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
    else
    {
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void *>(0));
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void *>(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void *>(6 * sizeof(float)));
        glEnableVertexAttribArray(2);
        unsigned int err = glGetError();
        if (err != GL_NO_ERROR)
        {
            throw std::runtime_error("Failed to set Vertice or Indice Data to Buffers: " + std::to_string(err));
        }
    }
}
glm::vec3 &entity::getMin()
{
    return min;
}

glm::vec3 &entity::getMax()
{
    return max;
}

collision *entity::getCollision()
{
    return collision ? collision.get() : nullptr;
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

glm::vec3 &entity::getPosition()
{
    return position;
}

glm::vec3 &entity::getAcceleration()
{
    return acceleration;
}

bool entity::getIsPolygonMode()
{
    return isPolygonMode;
}

bool entity::getHasTexture()
{
    return hasTexture;
}

float entity::getMass()
{
    return mass;
}

glm::vec3 &entity::getRotation()
{
    return rotation;
}

glm::vec3 &entity::getScale()
{
    return scale;
}

std::vector<float> &entity::getCoordData()
{
    return coordData;
}

std ::vector<unsigned int> &entity::getIndiceData()
{
    return indiceData;
}

glm::mat4 &entity::getModelMatrix()
{
    return modelMatrix;
}

void entity::setMax(const glm::vec3 &data)
{
    max = data;
}

void entity::setMin(const glm::vec3 &data)
{
    min = data;
}

void entity::setCollision(std::unique_ptr<class collision> data)
{
    collision = std::move(data);
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

void entity::setPosition(const glm::vec3 &data)
{
    position = data;
}

void entity::setAcceleration(const glm::vec3 &data)
{
    acceleration = data;
}

void entity::setIsPolygonMode(const bool &data)
{
    isPolygonMode = data;
}

void entity::setHasTexture(const bool &data)
{
    hasTexture = data;
}

void entity::setMass(const float &data)
{
    mass = data;
}

void entity::setRotation(const glm::vec3 &data)
{
    rotation = data;
}

void entity::setScale(const glm::vec3 &data)
{
    scale = data;
}

void entity::setCoordData(const std::vector<float> &data)
{
    coordData = data;
}

void entity::setIndiceData(const std::vector<unsigned int> &data)
{
    indiceData = data;
}

void entity::setModelMatrix(const glm::mat4 &data)
{
    modelMatrix = data;
}
