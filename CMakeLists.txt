# The cmake files should be rewritten
# There should be multiple CMakeLists.txt for each directory
# FIXME:


cmake_minimum_required(VERSION 3.29.6)
project(cormat)
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
add_executable(cormat  ${SOURCE} )



target_link_libraries(cormat glfw)




