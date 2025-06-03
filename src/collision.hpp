#pragma once
#include "buffer.hpp"
#include <glm/glm.hpp>
#include <stdexcept>
#include <vector>
class camera;
class shader;
class entity;
class collisionBox : buffer
{
  public:
    collisionBox(const entity &entity);
    void draw(entity &entity, camera camera, shader shader);
    std::vector<float> getVerticeData(glm::vec3 min, glm::vec3 max);
    glm::vec3 min, max;
    std::vector<float> verticeData;
    void setBuffer();
    std::vector<unsigned int> indiceData;
};
