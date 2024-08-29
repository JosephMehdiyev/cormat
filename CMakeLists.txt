# This is the initical CMAKE setup
# I am planning to change it to a nested cmake txt setup once the project gets bigger
# for now, this is enough


cmake_minimum_required(VERSION 3.29.6)
project(cormat
        VERSION 0.0.1
        DESCRIPTION "A 3D software for visualization of mathematical graphs"
        HOMEPAGE_URL "https://github.com/JosephMehdiyev/cormat"
        LANGUAGES CXX C
        )

include_directories(${cormat_SOURCE_DIR}/lib/glad)
include_directories(${cormat_SOURCE_DIR}/lib/stb_image)
include_directories(${cormat_SOURCE_DIR}/lib/glfw)


find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
file(GLOB_RECURSE SOURCE 
    lib/stb_image/*.c
    lib/stb_image/*.h
    lib/glad/glad.c
    lib/glad/glad.h
    src/*.c
    src/*.hpp
    src/*.h
    src/*.cpp)

add_executable(cormat  ${SOURCE})



target_link_libraries(cormat glfw)




