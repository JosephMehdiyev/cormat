#pragma once
#include "buffer.hpp"
#include "math.h"
#include <glm/glm.hpp>

#include <stdexcept>
#include <vector>

class entity;
class sphere;
class engineFloor;
class collision
{
  public:
    static bool checkCollisions(entity &first, entity &second);
    static void handleCollisions(entity &first, entity &second);

  private:
    static bool isCollidingSphereAABB(sphere &sphere, entity &AABB);
    static bool isCollidingAABBAABB(entity &entity1, entity &entity2);
    static bool isCollidingSphereSphere(sphere &sphere1, sphere &sphere2);
};
