#pragma once
#include "buffer.hpp"
#include "entity.hpp"

class collisionBox : public bufferObject
{
  public:
    collisionBox(entity &entity);
    void draw(camera &camera, shader &shader) override;
    void updateModelMatrix(entity &entity);

    // Setters
    void setMin(entity &entity);
    void setMax(entity &entity);
    // Getters
    glm::vec3 &getMin();
    glm::vec3 &getMax();
    void initializeMinMax(entity &entity);
    void updateMinMax(entity &entity);

  private:
    std::vector<float> generateVerticeData(glm::vec3 min, glm::vec3 max);
    glm::vec3 min, max;
};
