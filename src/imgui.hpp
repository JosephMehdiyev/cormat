#include "glad.h"
#include "glfwCamera.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

// #include "texture.hpp"
#include "graph.hpp"
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class myGui
{
  public:
    static void initializeGui();
    static void setupPlatform(glfwCamera glfwCamera);
    static void startGuiFrames();
    static void renderGuiFrames();
    static void closeGui();
    static void mainGui(glfwCamera &glfwCamera, graph &graph);
};
