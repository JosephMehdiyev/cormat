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
class engineFloor;
class collision : buffer
{
  public:
    collision(entity &entity);
    void draw(camera camera, shader shader);
    std::vector<float> getVerticeData(glm::vec3 min, glm::vec3 max);
    glm::vec3 min, max;
    std::vector<float> verticeData;
    void setBuffer();
    std::vector<unsigned int> indiceData;
    static bool checkCollisions(entity &first, entity &second);

  private:
    static bool isCollidingSphereAABB(sphere &sphere, entity &AABB);
    static bool isCollidingAABBAABB(entity &entity1, entity &entity2);
    static bool isCollidingSphereSphere(sphere &sphere1, sphere &sphere2);
    static bool isPointInsideSphere(glm::vec3 &point, sphere &sphere);
};
