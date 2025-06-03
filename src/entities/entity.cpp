#include "entity.hpp"
#include <memory>

entity::entity() {};

void entity::draw(camera camera, shader shader)
{
    updateModelMatrix(camera, shader);
    glBindVertexArray(VAO);
    if (hasTexture)
        shader.setBool("useTexture", true);
    else
        shader.setBool("useTexture", false);
    if (isPolygonMode)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINES);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDrawElements(GL_TRIANGLES, indiceData.size(), GL_UNSIGNED_INT, 0);
};

void entity::updateModelMatrix(camera camera, shader shader)
{
    // modelMatrix = glm::rotate(modelMatrix, static_cast<float>(glm::radians(camera.changeInX)), glm::vec3(0.0f, 1.0f, 0.0f));
    // modelMatrix = glm::rotate(modelMatrix, static_cast<float>(glfwGetTime() * camera.cameraRotationSpeed), glm::vec3(0.0f, 1.0f, 0.0f));
    // modelMatrix = glm::rotate(modelMatrix, static_cast<float>(glm::radians(camera.changeInY)), glm::vec3(1.0f, 0.0f, 0.0f));
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
    glBufferData(GL_ARRAY_BUFFER, 
                 static_cast<long long int>(sizeof(float) * coordData.size()),
                 &coordData[0],
                 GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 static_cast<long long int>(sizeof(unsigned int) * indiceData.size()),
                 &indiceData[0],
                 GL_STATIC_DRAW);


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

