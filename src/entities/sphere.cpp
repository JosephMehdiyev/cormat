#include "sphere.hpp"
#include "collisionBox.hpp"
// https://songho.ca/opengl/gl_sphere.html
sphere::sphere(float radius, int sectors, int stacks)
{
    setCollisionType(COLLISION_TYPE::SPHERE);

    this->radius = radius;
    const float PI = 3.1415926f;
    float x, y, z, xy;
    std::vector<float> localVerticeData;
    std::vector<unsigned int> localIndiceData;

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
            localVerticeData.insert(localVerticeData.end(), {x, y, z});

            localVerticeData.insert(localVerticeData.end(), {0.0f, 0.0f, 0.0f});
        }
    }
    setVerticeData(localVerticeData);

    for (int i = 0; i < stacks; ++i)
    {
        unsigned int k1 = i * (sectors + 1);
        unsigned int k2 = k1 + sectors + 1;

        for (int j = 0; j < sectors; ++j, ++k1, ++k2)
        {
            if (i != 0)
            {
                localIndiceData.insert(localIndiceData.end(), {k1, k2, k1 + 1});
            }
            if (i != stacks - 1)
            {
                localIndiceData.insert(localIndiceData.end(), {k1 + 1, k2, k2 + 1});
            }
        }
    }
    setIndiceData(localIndiceData);
    setVelocity({0.5f, 1.0f, 0.5f});
    setAcceleration({0.00, -9.8f, 0.0f});
    setPosition({0.0f, 20.0f, 0.0f});
    setCollisionBox(nullptr);
};
