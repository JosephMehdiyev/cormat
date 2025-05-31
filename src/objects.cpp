#include "objects.hpp"

cube::cube()
{
    coordData = {
        -0.5f, -0.5f, -0.5f, BLACK, 0.5f, -0.5f, -0.5f, BLACK, 0.5f, 0.5f, -0.5f, BLACK, -0.5f, 0.5f, -0.5f, BLACK,
        -0.5f, -0.5f, 0.5f,  BLACK, 0.5f, -0.5f, 0.5f,  BLACK, 0.5f, 0.5f, 0.5f,  BLACK, -0.5f, 0.5f, 0.5f,  BLACK,
    };
    indiceData = {
        //
        0, 1, 2, 2, 3, 0,
        //
        4, 5, 6, 6, 7, 4,
        //
        4, 0, 3, 3, 7, 4,
        //
        1, 5, 6, 6, 2, 1,
        //
        4, 5, 1, 1, 0, 4,
        //
        3, 2, 6, 6, 7, 3
        //
    };
};
