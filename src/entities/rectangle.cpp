#include "rectangle.hpp"

rectangle::rectangle(float a, float b)
{
    float halfA = a / 2;
    float halfB = b / 2;

    coordData = 
    {
        -halfA, -halfB, -halfA, BLACK,
         halfA, -halfB, -halfA, BLACK,
         halfA,  halfB, -halfA, BLACK,
        -halfA,  halfB, -halfA, BLACK,

        -halfA, -halfB, halfA,  BLACK,
         halfA, -halfB, halfA,  BLACK,
         halfA,  halfB, halfA,  BLACK,
        -halfA,  halfB, halfA,  BLACK,
    };

    indiceData = 
    {
        0, 1, 2, 2, 3, 0,
        4, 5, 6, 6, 7, 4,
        4, 0, 3, 3, 7, 4,
        1, 5, 6, 6, 2, 1,
        4, 5, 1, 1, 0, 4,
        3, 2, 6, 6, 7, 3
    };
}


engineFloor::engineFloor(float a, float b)
{
    float halfA = a / 2;
    float halfB = b / 2;


    scale = glm::vec3(500.0f);
    rotation.x = 90.0f;

    type = bodyType::STATIC;
    coordData = 
    {
        -halfA, -halfB, 0.0f, BLACK, 0.0f, 0.0f,
        halfA,  -halfB, 0.0f, BLACK, 1.0f, 0.0f,
        halfA,  halfB,  0.0f, BLACK, 1.0f, 1.0f,
        -halfA, halfB,  0.0f, BLACK, 0.0f, 1.0f
    };
    indiceData = 
    {
        0, 1, 2, 2, 3, 0,
    };
    hasTexture = true;

};

