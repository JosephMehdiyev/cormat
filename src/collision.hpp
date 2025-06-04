#pragma once
#include "buffer.hpp"
#include "math.h"
#include <glm/glm.hpp>
#include <stdexcept>
#include <vector>
class camera;
class shader;
class entity;
class sphere;
class collision : buffer
{
  public:
    collision(const entity &entity);
    void draw(entity &entity, camera camera, shader shader);
    std::vector<float> getVerticeData(glm::vec3 min, glm::vec3 max);
    glm::vec3 min, max;
    std::vector<float> verticeData;
    void setBuffer();
    std::vector<unsigned int> indiceData;
    static bool isCollidingSphereAABB(const entity &AABB, const sphere &sphere);
    static bool isCollidingSphereSphere(const sphere &sphere1, const sphere &sphere2);
    static bool isPointInsideSphere(const glm::vec3 &point, const sphere &sphere);
};
