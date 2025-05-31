#include "glad.h"
#include "glfwWindow.hpp"
#include "imgui.h"
#include "imgui.hpp"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
// #include "texture.hpp"
#include "render.hpp"
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int main()
{
    glfwWindow glfwCamera(SCR_WIDTH, SCR_HEIGHT);
    render graph;
    myGui::initializeGui();
    myGui::setupPlatform(glfwCamera);

    while (!glfwWindowShouldClose(glfwCamera.window))
    {
        glfwPollEvents();
        myGui::startGuiFrames();
        myGui::mainGui(glfwCamera.worldCamera);
        glfwCamera.getInput();
        graph.start(glfwCamera.worldCamera);
        myGui::renderGuiFrames();
        glfwCamera.swapBuffers();
    }
    myGui::closeGui();
    glfwTerminate();
    return 0;
}
