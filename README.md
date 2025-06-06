### The project will be repurposed as a 3D Physics Engine! This project is no longer for drawing Graphs
# About the project (In development) ![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=Plastic&logo=c%2B%2B&logoColor=white) ![OpenGL](https://img.shields.io/badge/OpenGL-%23FFFFFF.svg?style=Plastic&logo=opengl) ![CMake](https://img.shields.io/badge/CMake-%23008FBA.svg?style=Plastic&logo=cmake&logoColor=white)
**Cormat** is a graphical 3D math software intended for visualizing mathematical functions. In the future, I am planning to make this project expand to a 3D engine, mainly for physics simulations. Currently, it only is a graph software.
# TODO
* Min/Max, collision box rendering and making are very buggy: FIX
* Min/Max updating is also buggy, if object is not static it will cause problems
# Dependecies
* [OpenGL](https://www.khronos.org/opengl/wiki/Getting_Started#Downloading_OpenGL)  API for rendering 2D-3D graphics
* [GLFW](https://github.com/glfw/glfw) API for creating windows, reading input and handling events. **CMAKE AUTOMATICALLY INSTALLS LOCALLY VIA GIT**
* [stb_image](https://github.com/nothings/stb/blob/master/stb_image.h) for textures
* [GLM](https://github.com/g-truc/glm) for linear algebra, trigonometry and calculus.
* [CMAKE](https://cmake.org/about/) to generate make files
* [GCC](https://gcc.gnu.org/install/) to compile the project

# Shortcuts
* Use mouse scrool to zoom in and out
* Use W,A,S,D to move around
# Build
**NOTE:** I only tested this program for linux, be vary.
To build and run, run these commands.
```
git clone https://github.com/JosephMehdiyev/cormat
cd cormat # the directory may vary, just cd to the project root
mkdir build
cd build
cmake --preset release -S ../ -B . # you may also use --preset debug or --preset default, release is recommended
make
./cormat
```
I only compiled this in Linux ARCH. I did not test this program on other distros.
There are no system specific code in the project (yet? imgui may give error). I believe it should run smoothly on all the popular systems.
In future, there will be precompiled binaries for WINDOWS/LINUX/MACOS.
# Gallery 
300 Sphere Elastic, no Friction, no Energy Loss Collessions
![](./gallery/scene.gif)
# License
The project is licensed under the GNU GENERAL PUBLIC LICENSE.




