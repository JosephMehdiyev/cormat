#pragma once
#include "entity.hpp"

class rectangle : public entity
{
  public:
    rectangle(float a = 0.5f, float b = 0.5f);
};


class engineFloor : public entity
{
  public:
    engineFloor(float a = 0.5f, float b = 0.5f);
};
