#pragma once
#include "buffer.hpp"
#include "camera.hpp"
#include "glad.h"
#include "shader.hpp"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>

#define BLACK 0.0f, 0.0f, 0.0f
#define WHITE 1.0f, 1.0f, 1.0f
#define RED 1.0f, 0.0f, 0.0f
#define GREEN 0.0f, 1.0f, 0.0f
#define BLUE 0.0f, 0.0f, 1.0f

enum class bodyType
{
    STATIC,
    DYNAMIC,
};

class object : public buffer
{
  public:
    object();
    void draw(camera camera, shader shader);
    std::vector<float> coordData;
    std::vector<unsigned int> indiceData;
    glm::mat4 modelMatrix;
    glm::vec3 velocity{0.0f, 0.0f, 0.0f};
    glm::vec3 acceleration{0.0f, 0.0f, 0.0f};
    glm::vec3 position{0.0f, 0.0f, 0.0f};
    bodyType type = bodyType::DYNAMIC;
    float mass = 1.0f;
    glm::vec3 rotation{0.0f, 0.0f, 0.0f};
    glm::vec3 scale = glm::vec3(1.0f);
    void updateModelMatrix(camera camera, shader shader);
    bool isPolygonMode = false;
    bool hasTexture = false;
    void setBuffer();

  private:
};

class cube : public object
{
  public:
    cube();
};

class sphere : public object
{
  public:
    sphere(float radius = 1.0f, int sectors = 36, int stacks = 18);
};

class engineFloor : public object
{
  public:
    engineFloor(float a = 0.3f, float b = 0.1f);
};
