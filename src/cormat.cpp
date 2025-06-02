#include "glad.h"
#include "glfwWindow.hpp"
#include "imgui.h"
#include "imgui.hpp"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "render.hpp"
#include "texture.hpp"
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int main()
{
    glfwWindow glfwCamera(SCR_WIDTH, SCR_HEIGHT);
    texture texture("../data/textures/dark.png");

    render scene;
    myGui::initializeGui();
    myGui::setupPlatform(glfwCamera);
    double lastTime = glfwGetTime();

    while (!glfwWindowShouldClose(glfwCamera.window))
    {
        double currentTime = glfwGetTime();
        double deltaT = currentTime - lastTime;
        lastTime = currentTime;
        deltaT = std::min(deltaT, 0.1);
        glfwCamera.showFPS();

        glfwPollEvents();
        myGui::startGuiFrames();
        myGui::mainGui(glfwCamera.worldCamera);

        glUniform1i(glGetUniformLocation(scene.shader.shaderProgramID, "TEXTURE_EXAMPLE"), 0);

        glfwCamera.getInput();
        glfwCamera.worldCamera.updateCameraVectors();
        scene.start(glfwCamera.worldCamera, deltaT);
        myGui::renderGuiFrames();
        glfwCamera.swapBuffers();
    }
    myGui::closeGui();
    glfwTerminate();
    return 0;
}
