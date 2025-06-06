#pragma once
#include "buffer.hpp"
#include "collision.hpp"
#include "glad.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <memory>
#include <vector>

#define BLACK 0.0f, 0.0f, 0.0f
#define WHITE 1.0f, 1.0f, 1.0f
#define RED 1.0f, 0.0f, 0.0f
#define GREEN 0.0f, 1.0f, 0.0f
#define BLUE 0.0f, 0.0f, 1.0f

class collisionBox;

enum class BODY_TYPE
{
    STATIC,
    DYNAMIC,
};

enum class COLLISION_TYPE
{
    AABB,
    SPHERE
};

class entity : public bufferObject
{
  public:
    entity();
    virtual ~entity();
    bool isStatic();
    bool isDynamic();

    // Getters
    class collisionBox *getCollisionBox();
    COLLISION_TYPE &getCollisionType();
    BODY_TYPE &getBodyType();
    glm::vec3 &getVelocity();
    glm::vec3 &getAcceleration();
    float getMass();

    // Setters
    void setCollisionBox(std::unique_ptr<class collisionBox> data);
    void setCollisionType(const COLLISION_TYPE &data);
    void setBodyType(const BODY_TYPE &data);
    void setVelocity(const glm::vec3 &data);
    void setAcceleration(const glm::vec3 &data);
    void setMass(const float &data);

    bool isSphere() const
    {
        return collisionType == COLLISION_TYPE::SPHERE;
    }
    bool isAABB() const
    {
        return collisionType == COLLISION_TYPE::AABB;
    }

  private:
    float mass = 1.0f;

    COLLISION_TYPE collisionType = COLLISION_TYPE::AABB;
    BODY_TYPE bodyType = BODY_TYPE::DYNAMIC;
    std::unique_ptr<class collisionBox> collisionBox;

    glm::vec3 velocity{0.0f, 0.0f, 0.0f};
    glm::vec3 acceleration{0.0f, 0.0f, 0.0f};
    glm::vec3 centerMass;

    float angularVelocity = 0;
    float angularAcceleration = 0;

    float kineticEnergy;
    float potentialEnergy;
};
