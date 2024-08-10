# The cmake files should be rewritten
# There should be multiple CMakeLists.txt for each directory
# FIXME:


cmake_minimum_required(VERSION 3.29.6)
project(cormat)
include_directories(${cormat_SOURCE_DIR}/lib/glad)
include_directories(${cormat_SOURCE_DIR}/lib/stb_image)


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
set(CMAKE_CXX_FLAGS "-pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=3 -Wswitch-default -Wundef -Werror -Wno-unused -O3 -g")
message(STATUS "CXX FLAGS = ${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_COMPILER "/usr/bin/g++")
message(STATUS "CXX compiler = ${CMAKE_CXX_COMPILER}")
set(CMAKE_EXPORT_COMPILE_COMMANDS "ON")
message(STATUS "EXPORT COMPILE COMMANDS ${CMAKE_EXPORT_COMPILE_COMMANDS}")
add_executable(cormat  ${SOURCE} )



target_link_libraries(cormat glfw)




