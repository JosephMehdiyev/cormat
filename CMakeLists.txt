set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_LIST_DIR}/cmake")
include(libraries)


cmake_minimum_required(VERSION 3.29.6)
project(cormat
        VERSION 0.0.1
        DESCRIPTION "A 3D software for visualization of mathematical graphs"
        HOMEPAGE_URL "https://github.com/JosephMehdiyev/cormat"
        LANGUAGES CXX C
)

set(GLFW_BUILD_TESTS OFF CACHE BOOL "Disable building GLFW tests" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Disable building GLFW examples" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "Disable building GLFW documentation" FORCE)
FetchContent_MakeAvailable(glfw)

include_directories(${cormat_SOURCE_DIR}/lib/glad)
include_directories(${cormat_SOURCE_DIR}/lib/stb_image)


find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)
file(GLOB_RECURSE SOURCE 
    lib/stb_image/*.cpp
    lib/stb_image/*.hpp
    lib/glad/glad.c
    lib/glad/glad.h
    src/*.c
    src/*.hpp
    src/*.h
    src/*.cpp)

add_executable(cormat  ${SOURCE})



target_link_libraries(cormat glfw)




