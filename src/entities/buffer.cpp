#include "buffer.hpp"
#include "entity.hpp"
#include <GL/gl.h>
#include <stdexcept>

bufferObject::bufferObject()
{
    initBuffer();
}
void

bufferObject::initBuffer()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    unsigned int err = glGetError();
    if (err != GL_NO_ERROR)
    {
        deleteBuffer();
        throw std::runtime_error("Failed to Generate OpenGL Buffers: " + std::to_string(err));
    }
}

void bufferObject::deleteBuffer()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

bufferObject::~bufferObject()
{
    deleteBuffer();
}

void bufferObject::setBuffer()
{
    if (verticeData.empty())
        throw std::invalid_argument("Vertice Data Cannot be Empty");
    if (indiceData.empty())
        throw std::invalid_argument("Indice Data Cannot be Empty");
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * verticeData.size(), &verticeData[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indiceData.size(), &indiceData[0], GL_STATIC_DRAW);
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

void bufferObject::draw(camera &camera, shader &shader)
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

void bufferObject::updateModelMatrix(camera &camera, shader &shader)
{
    // modelMatrix = glm::rotate(modelMatrix, static_cast<float>(glm::radians(camera.changeInX)), glm::vec3(0.0f, 1.0f,
    // 0.0f)); modelMatrix = glm::rotate(modelMatrix, static_cast<float>(glfwGetTime() * camera.cameraRotationSpeed),
    // glm::vec3(0.0f, 1.0f, 0.0f)); modelMatrix = glm::rotate(modelMatrix,
    // static_cast<float>(glm::radians(camera.changeInY)), glm::vec3(1.0f, 0.0f, 0.0f));
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)); // X-axis
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)); // Y-axis
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f)); // Z-axis
    modelMatrix = glm::scale(modelMatrix, scale);
    modelMatrix = glm::translate(modelMatrix, position);

    glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgramID, "model"), 1, GL_FALSE, &modelMatrix[0][0]);
}

void bufferObject::setVerticeData(const std::vector<float> &data)
{
    verticeData = data;
}

void bufferObject::setIndiceData(const std::vector<unsigned int> &data)
{
    indiceData = data;
}

void bufferObject::setHasTexture(const bool &data)
{
    hasTexture = data;
}

void bufferObject::setIsPolygonMode(const bool &data)
{
    isPolygonMode = data;
}

void bufferObject::setRotation(const glm::vec3 &data)
{
    rotation = data;
}

void bufferObject::setScale(const glm::vec3 &data)
{
    scale = data;
}

void bufferObject::setPosition(const glm::vec3 &data)
{
    position = data;
}

bool bufferObject::getIsPolygonMode()
{
    return isPolygonMode;
}

glm::vec3 &bufferObject::getRotation()
{
    return rotation;
}

glm::vec3 &bufferObject::getScale()
{
    return scale;
}

glm::vec3 &bufferObject::getPosition()
{
    return position;
}

std::vector<unsigned int> &bufferObject::getIndiceData()
{
    return indiceData;
}

glm::mat4 &bufferObject::getModelMatrix()
{
    return modelMatrix;
}
