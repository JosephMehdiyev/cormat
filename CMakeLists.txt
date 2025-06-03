set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_LIST_DIR}/cmake")

## ln -s build/compile_commands.json ../compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

execute_process(
  COMMAND ${CMAKE_COMMAND} -E create_symlink
          ${CMAKE_BINARY_DIR}/compile_commands.json
          ${CMAKE_SOURCE_DIR}/compile_commands.json
  RESULT_VARIABLE result
)
include(libraries)


cmake_minimum_required(VERSION 3.29.6)
project(cormat
        VERSION 0.0.1
        DESCRIPTION "3D Physics Engine made from scratch"
        HOMEPAGE_URL "https://github.com/JosephMehdiyev/cormat"
        LANGUAGES CXX C
)

set(GLFW_BUILD_TESTS OFF CACHE BOOL "Disable building GLFW tests" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Disable building GLFW examples" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "Disable building GLFW documentation" FORCE)

message("Fetching glfw")
FetchContent_MakeAvailable(glfw)
include_directories(${glm_SOURCE_DIR})
include_directories(${cormat_SOURCE_DIR}/src)
include_directories(${cormat_SOURCE_DIR}/src/entities)
include_directories(${cormat_SOURCE_DIR}/lib/glad)
include_directories(${cormat_SOURCE_DIR}/lib/stb_image)


find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)

file(GLOB_RECURSE SOURCE 
    lib/stb_image/*.cpp
    lib/stb_image/*.hpp
    lib/glad/glad.c
    lib/glad/glad.h
    src/entities/*.cpp
    src/entities/*.hpp
    src/*.c
    src/*.hpp
    src/*.h
    src/*.cpp)

add_executable(cormat  ${SOURCE})
add_subdirectory(lib)

target_link_libraries(cormat glfw imgui)
