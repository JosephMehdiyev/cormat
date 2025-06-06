#include "rectangle.hpp"
#include "collisionBox.hpp"

rectangle::rectangle(float width, float height, float thickness)
{

    float halfA = width / 2;
    float halfB = height / 2;
    float halfC = thickness / 2;
    this->width = halfA;
    this->height = halfB;
    this->thickness = halfC;

    setVerticeData({
        -halfA, -halfB, -halfC, BLACK, halfA,  -halfB, -halfC, BLACK,
        halfA,  halfB,  -halfC, BLACK, -halfA, halfB,  -halfC, BLACK,

        -halfA, -halfB, halfC,  BLACK, halfA,  -halfB, halfC,  BLACK,
        halfA,  halfB,  halfC,  BLACK, -halfA, halfB,  halfC,  BLACK,
    });

    setIndiceData(
        {0, 1, 2, 2, 3, 0, 4, 5, 6, 6, 7, 4, 4, 0, 3, 3, 7, 4, 1, 5, 6, 6, 2, 1, 4, 5, 1, 1, 0, 4, 3, 2, 6, 6, 7, 3});
}

rectangle::rectangle(float width, float height)
{
    float halfA = width / 2;
    float halfB = height / 2;

    this->width = halfA;
    this->height = halfB;
    setScale(glm::vec3(500.0f));
    setRotation({90.0f, 0.0f, 0.0f});
    setBodyType(BODY_TYPE::STATIC);
    setVerticeData({-halfA, -halfB, 0.0f, BLACK, 0.0f, 0.0f, halfA,  -halfB, 0.0f, BLACK, 1.0f, 0.0f,
                    halfA,  halfB,  0.0f, BLACK, 1.0f, 1.0f, -halfA, halfB,  0.0f, BLACK, 0.0f, 1.0f});
    setIndiceData({
        0,
        1,
        2,
        2,
        3,
        0,
    });
    setHasTexture(true);
    setCollisionBox(std::make_unique<class collisionBox>(*this));
};

float &rectangle::getWidth()
{
    return width;
}

float &rectangle::getHeight()
{
    return height;
}

float &rectangle::getThickness()
{
    return thickness;
}
