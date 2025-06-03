#include "objects.hpp"

object::object() {};

void object::draw(camera camera, shader shader)
{
    updateModelMatrix(camera, shader);
    glBindVertexArray(VAO);
    if (hasTexture)
        shader.setBool("useTexture", true);
    else
        shader.setBool("useTexture", false);
    if (isPolygonMode)
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDrawElements(GL_TRIANGLES, indiceData.size(), GL_UNSIGNED_INT, 0);
};

void object::updateModelMatrix(camera camera, shader shader)
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

cube::cube()
{

    coordData = {
        -0.5f, -0.5f, -0.5f, BLACK, 0.5f, -0.5f, -0.5f, BLACK, 0.5f, 0.5f, -0.5f, BLACK, -0.5f, 0.5f, -0.5f, BLACK,
        -0.5f, -0.5f, 0.5f,  BLACK, 0.5f, -0.5f, 0.5f,  BLACK, 0.5f, 0.5f, 0.5f,  BLACK, -0.5f, 0.5f, 0.5f,  BLACK,
    };
    indiceData = {
        //
        0, 1, 2, 2, 3, 0,
        //
        4, 5, 6, 6, 7, 4,
        //
        4, 0, 3, 3, 7, 4,
        //
        1, 5, 6, 6, 2, 1,
        //
        4, 5, 1, 1, 0, 4,
        //
        3, 2, 6, 6, 7, 3
        //
    };
}

// https://songho.ca/opengl/gl_sphere.html
sphere::sphere(float radius, int sectors, int stacks)
{
    // Generate vertices (positions + colors)
    const float PI = 3.1415926f;
    float x, y, z, xy; // Vertex position
    float s, t;        // TexCoords (optional)

    for (int i = 0; i <= stacks; ++i)
    {
        float stackAngle = PI / 2 - i * PI / stacks; // From -π/2 to π/2
        xy = radius * cosf(stackAngle);
        z = radius * sinf(stackAngle);

        for (int j = 0; j <= sectors; ++j)
        {
            float sectorAngle = j * 2 * PI / sectors; // From 0 to 2π

            // Position
            x = xy * cosf(sectorAngle);
            y = xy * sinf(sectorAngle);
            coordData.insert(coordData.end(), {x, y, z});

            coordData.insert(coordData.end(), {0.0f, 0.0f, 0.0f});
        }
    }

    for (int i = 0; i < stacks; ++i)
    {
        unsigned int k1 = i * (sectors + 1);
        unsigned int k2 = k1 + sectors + 1;

        for (int j = 0; j < sectors; ++j, ++k1, ++k2)
        {
            if (i != 0)
            {
                indiceData.insert(indiceData.end(), {k1, k2, k1 + 1});
            }
            if (i != stacks - 1)
            {
                indiceData.insert(indiceData.end(), {k1 + 1, k2, k2 + 1});
            }
        }
    }

    modelMatrix = glm::mat4(1.0f);
    position = {0.0f, 10.0f, 0.0f};
};

engineFloor::engineFloor(float a, float b)
{
    scale = glm::vec3(500.0f);
    rotation.x = 90.0f;

    type = bodyType::STATIC;
    coordData = {-0.5f, -0.5f, 0.0f, BLACK, 0.0f, 0.0f, 0.5f,  -0.5f, 0.0f, BLACK, 1.0f, 0.0f,
                 0.5f,  0.5f,  0.0f, BLACK, 1.0f, 1.0f, -0.5f, 0.5f,  0.0f, BLACK, 0.0f, 1.0f};
    indiceData = {
        //
        0, 1, 2, 2, 3, 0,
        //
    };
    hasTexture = true;
};

void object::setBuffer()
{
    if (coordData.empty())
        throw std::invalid_argument("Vertice Data Cannot be Empty");
    if (indiceData.empty())
        throw std::invalid_argument("Indice Data Cannot be Empty");
    if (!hasTexture)
    {
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, static_cast<long long int>(sizeof(float) * coordData.size()), &coordData[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<long long int>(sizeof(unsigned int) * indiceData.size()), &indiceData[0], GL_STATIC_DRAW);
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
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, static_cast<long long int>(sizeof(float) * coordData.size()), &coordData[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<long long int>(sizeof(unsigned int) * indiceData.size()), &indiceData[0], GL_STATIC_DRAW);
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
