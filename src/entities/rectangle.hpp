#pragma once
#include "entity.hpp"

class rectangle : public entity
{
  public:
    rectangle(float a = 0.5f, float b = 0.5f);
    rectangle(float a = 0.5f, float b = 0.5f, std::string isFloor = "FLOOR");
};
