# About the project ![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=Plastic&logo=c%2B%2B&logoColor=white) ![OpenGL](https://img.shields.io/badge/OpenGL-%23FFFFFF.svg?style=Plastic&logo=opengl) ![CMake](https://img.shields.io/badge/CMake-%23008FBA.svg?style=Plastic&logo=cmake&logoColor=white)
**Cormat** is a graphical 3D math software intended for visualizing mathematical functions. In the future, I am planning to make this project expand to a 3D engine, mainly for physics simulations. Currently, it only is a graph software.
# Roadmap
I want to remind you that I am also very busy with my other projects. Therefore the development will be slow, especially the simulation part, since I have to learn lots of new things to do that.
* ~~**Rotation input** Change the way the rotation of the graph is handled, change the cursor type to the visible.~~
* <span style="color:red">**IMPORTANT BUG:**</span> Whenever the program is run, there is a change it throws a segmentation fault. With running multiple times, eventually it be run succesfully.
* **MAIN CORE** A point generator from mathematical functions to draw the graphs. Afterwards, the verison **0.1.0** will be ready
* **BINARIES** Precompiled binaries for WINDOWS/LINUX (arch/ubuntu)/MACOS. This will be done after the verison 0.1.0 release
* **CMAKE** currently the way I generate my make files are in mess. I am planning to completely change the structure of cmake

* **2D/3D mode** A feature to change between the dimensions
* **Polyhon/Line/Point mode** A feature to change between the style of the graph
* **User Interface, ImGui** A small settings window to change the settings of the graph
* **Anti-aliasing** To increase the details of the graph, making individual pixels more invisible
* **FUTURE** I have not yet planed it in detail, but the software will have simulation features
# Dependecies
* [OpenGL](https://www.khronos.org/opengl/wiki/Getting_Started#Downloading_OpenGL)  API for rendering 2D-3D graphics
* [GLFW](https://github.com/glfw/glfw) API for creating windows, reading input and handling events
* [stb_image](https://github.com/nothings/stb/blob/master/stb_image.h) for textures
* [GLM](https://github.com/g-truc/glm) for linear algebra, trigonometry and calculus.
* [CMAKE](https://cmake.org/about/) to generate make files
* [GCC](https://gcc.gnu.org/install/) to compile the project

# Shortcuts
* Use mouse to rotate the graph
* Use mouse scrool to zoom in and out
* Use W,A,S,D to move around
# Build

To build and run, run these commands.
```
git clone https://github.com/JosephMehdiyev/cormat
cd /to/your/folder/path
cd  build
cmake ..
make
./cormat
```
I only compiled this in Linux ARCH. I did not test this program on other distros.
In future, there will be precompiled binaries for WINDOWS/LINUX/MACOS. Do not worry!

# License
The project is licensed under the GNU GENERAL PUBLIC LICENSE.



