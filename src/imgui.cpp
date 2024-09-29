#include "imgui.hpp"
#include "imgui.h"

void
myGui::mainGui(glfwCamera &glfwCamera, graph &graph)
{
    ImVec2 windowSize(600,300);
    ImGui::SetWindowSize(windowSize);
    ImGui::Begin("Graph Control");
    ImGui::SliderFloat("Rotation speed", &glfwCamera.cameraRotationSpeed, 0, 3);
    ImGui::SliderFloat("Walk speed", &glfwCamera.cameraSpeed, 0, 3);

    float x = glfwCamera.cameraRotationSpeed;
    static int clickedRotateButton = 0;
    if (ImGui::Button("Stop/Start rotating"))
        clickedRotateButton++;
    if (clickedRotateButton & 1)
    {
        ImGui::SameLine();
        glfwCamera.cameraRotationSpeed = 0;
    }
    else glfwCamera.cameraRotationSpeed = x;

    ImGui::ShowDemoWindow();
    ImGui::End();
}













// Elementary functions to make imGui work
//
//
//


void
myGui::initializeGui()
{
     IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
}


void
myGui::setupPlatform(glfwCamera glfwCamera)
{
    ImGui_ImplGlfw_InitForOpenGL(glfwCamera.window, true);
    ImGui_ImplOpenGL3_Init();
}


void
myGui::startGuiFrames()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}


void
myGui::renderGuiFrames()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}


void
myGui::closeGui()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
