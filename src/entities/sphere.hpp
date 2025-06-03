#pragma once
#include "objects.hpp"

class sphere : public object
{
  public:
    sphere(float radius = 1.0f, int sectors = 36, int stacks = 18);
};
