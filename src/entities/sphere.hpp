#pragma once
#include "entity.hpp"

class sphere : public entity
{
  public:
    sphere(float radius = 1.0f, int sectors = 36, int stacks = 18);
    void setRadius(const float &data)
    {
        radius = data;
    };
    float &getRadius()
    {
        return radius;
    };

  private:
    float radius;
};
