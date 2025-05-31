#include "glad.h"
#include "glfwWindow.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

// #include "texture.hpp"
#include "render.hpp"
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class myGui
{
  public:
    static void initializeGui();
    static void setupPlatform(glfwWindow glfwCamera);
    static void startGuiFrames();
    static void renderGuiFrames();
    static void closeGui();
    static void mainGui(camera &camera);
};
