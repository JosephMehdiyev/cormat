#include "rectangle.hpp"

rectangle::rectangle(float a, float b)
{
    float halfA = a / 2;
    float halfB = b / 2;

    setCoordData({
        -halfA, -halfB, -halfA, BLACK, halfA,  -halfB, -halfA, BLACK,
        halfA,  halfB,  -halfA, BLACK, -halfA, halfB,  -halfA, BLACK,

        -halfA, -halfB, halfA,  BLACK, halfA,  -halfB, halfA,  BLACK,
        halfA,  halfB,  halfA,  BLACK, -halfA, halfB,  halfA,  BLACK,
    });

    setIndiceData(
        {0, 1, 2, 2, 3, 0, 4, 5, 6, 6, 7, 4, 4, 0, 3, 3, 7, 4, 1, 5, 6, 6, 2, 1, 4, 5, 1, 1, 0, 4, 3, 2, 6, 6, 7, 3});
    setMin({-halfA, -halfB, -halfA});
    setMax({halfA, halfB, halfA});
}

rectangle::rectangle(float a, float b, std ::string isFloor)
{
    if (isFloor == "FLOOR")
    {
        float halfA = a / 2;
        float halfB = b / 2;
        setScale(glm::vec3(500.0f));
        setRotation({90.0f, 0.0f, 0.0f});
        setBodyType(BODY_TYPE::STATIC);
        setCoordData({-halfA, -halfB, 0.0f, BLACK, 0.0f, 0.0f, halfA,  -halfB, 0.0f, BLACK, 1.0f, 0.0f,
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
        setMin({-halfA, -halfB, -0.01f});
        setMax({halfA, halfB, 0.01f});
        setCollision(std::make_unique<class collision>(*this));
    }
};
