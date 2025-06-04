#include "sphere.hpp"
// https://songho.ca/opengl/gl_sphere.html
sphere::sphere(float radius, int sectors, int stacks)
{

    this->radius = radius;
    const float PI = 3.1415926f;
    float x, y, z, xy;

    for (int i = 0; i <= stacks; ++i)
    {
        float stackAngle = PI / 2 - i * PI / stacks;
        xy = radius * cosf(stackAngle);
        z = radius * sinf(stackAngle);

        for (int j = 0; j <= sectors; ++j)
        {
            float sectorAngle = j * 2 * PI / sectors;

            // Position
            x = xy * cosf(sectorAngle);
            y = xy * sinf(sectorAngle);
            coordData.insert(coordData.end(), {x, y, z});

            coordData.insert(coordData.end(), {0.0f, 0.0f, 0.0f});
        }
    }

    for (int i = 0; i < stacks; ++i)
    {
        unsigned int k1 = i * (sectors + 1);
        unsigned int k2 = k1 + sectors + 1;

        for (int j = 0; j < sectors; ++j, ++k1, ++k2)
        {
            if (i != 0)
            {
                indiceData.insert(indiceData.end(), {k1, k2, k1 + 1});
            }
            if (i != stacks - 1)
            {
                indiceData.insert(indiceData.end(), {k1 + 1, k2, k2 + 1});
            }
        }
    }
    acceleration = {0.00, -9.8f, 0.0f};
    position = {0.0f, 10.0f, 0.0f};
    min = -glm::vec3(radius);
    max = +glm::vec3(radius);
    collision = std::make_unique<class collision>(*this);
};
