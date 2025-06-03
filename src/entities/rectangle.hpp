#pragma once
#include "objects.hpp"

class rectangle : public object
{
  public:
    rectangle(float a = 0.5f, float b = 0.5f);
};


class engineFloor : public object
{
  public:
    engineFloor(float a = 0.5f, float b = 0.5f);
};
