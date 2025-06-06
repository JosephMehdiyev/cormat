#pragma once
#include "entity.hpp"

class rectangle : public entity
{
  public:
    rectangle(float width, float height, float thickness);
    rectangle(float width, float height);
    void updateDimensions();
    float &getWidth();
    float &getHeight();
    float &getThickness();

  private:
    float width, height, thickness = 0;
};
