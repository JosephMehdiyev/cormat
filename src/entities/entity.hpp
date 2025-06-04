#pragma once
#include "buffer.hpp"
#include "camera.hpp"
#include "collision.hpp"
#include "glad.h"
#include "shader.hpp"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <memory>
#include <vector>

#define BLACK 0.0f, 0.0f, 0.0f
#define WHITE 1.0f, 1.0f, 1.0f
#define RED 1.0f, 0.0f, 0.0f
#define GREEN 0.0f, 1.0f, 0.0f
#define BLUE 0.0f, 0.0f, 1.0f

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

class entity : public buffer
{
  public:
    entity();
    virtual ~entity();
    void draw(const camera &camera, const shader &shader);
    void updateModelMatrix(camera camera, shader shader);
    void setBuffer();
    void disableCollision();

    // Getters
    glm::vec3 &getMin();
    glm::vec3 &getMax();
    class collision *getCollision();
    COLLISION_TYPE &getCollisionType();
    BODY_TYPE &getBodyType();
    glm::vec3 &getVelocity();
    glm::vec3 &getPosition();
    glm::vec3 &getAcceleration();
    bool getIsPolygonMode();
    bool getHasTexture();
    float getMass();
    glm::vec3 &getRotation();
    glm::vec3 &getScale();
    std::vector<float> &getCoordData();
    std::vector<unsigned int> &getIndiceData();
    glm::mat4 &getModelMatrix();
    // Setters
    void setMin(const glm::vec3 &data);
    void setMax(const glm::vec3 &data);
    void setCollision(std::unique_ptr<class collision> data);
    void setCollisionType(const COLLISION_TYPE &data);
    void setBodyType(const BODY_TYPE &data);
    void setVelocity(const glm::vec3 &data);
    void setPosition(const glm::vec3 &data);
    void setAcceleration(const glm::vec3 &data);
    void setIsPolygonMode(const bool &data);
    void setHasTexture(const bool &data);
    void setMass(const float &data);
    void setRotation(const glm::vec3 &data);
    void setScale(const glm::vec3 &data);
    void setCoordData(const std::vector<float> &data);
    void setIndiceData(const std::vector<unsigned int> &data);
    void setModelMatrix(const glm::mat4 &ata);

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
    std::unique_ptr<class collision> collision;
    glm::vec3 min, max;
    bool isPolygonMode = false;
    bool hasTexture = false;

    glm::vec3 velocity{0.0f, 0.0f, 0.0f};
    glm::vec3 acceleration{0.0f, 0.0f, 0.0f};
    glm::vec3 position{0.0f, 0.0f, 0.0f};

    glm::vec3 rotation{0.0f, 0.0f, 0.0f};
    glm::vec3 scale = glm::vec3(1.0f);

    std::vector<float> coordData;
    std::vector<unsigned int> indiceData;

    glm::mat4 modelMatrix;
};
