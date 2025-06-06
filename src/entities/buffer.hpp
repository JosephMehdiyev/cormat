#pragma once
#include "camera.hpp"
#include "glad.h"
#include "shader.hpp"
#include <GL/gl.h>
#include <vector>

class entity;

class bufferObject
{
  public:
    bufferObject();
    ~bufferObject();
    virtual void draw(camera &camera, shader &shader);
    void updateModelMatrix(camera &camera, shader &shader);
    void setBuffer();
    unsigned int &getVAO()
    {
        return VAO;
    }

    bool getIsPolygonMode();
    glm::vec3 &getPosition();
    glm::vec3 &getRotation();
    glm::vec3 &getScale();
    std::vector<unsigned int> &getIndiceData();
    glm::mat4 &getModelMatrix();

    void setVerticeData(const std::vector<float> &data);
    void setIndiceData(const std::vector<unsigned int> &data);
    void setHasTexture(const bool &data);
    void setIsPolygonMode(const bool &data);
    void setPosition(const glm::vec3 &data);
    void setRotation(const glm::vec3 &data);
    void setScale(const glm::vec3 &data);

  private:
    unsigned int VBO, VAO, EBO;
    glm::mat4 modelMatrix;

    std::vector<float> verticeData;
    std::vector<unsigned int> indiceData;
    bool isPolygonMode = false;

    bool hasTexture = false;

    glm::vec3 rotation{0.0f, 0.0f, 0.0f};
    glm::vec3 position{0.0f, 0.0f, 0.0f};
    glm::vec3 scale = glm::vec3(1.0f);

    void initBuffer();
    void deleteBuffer();
};
