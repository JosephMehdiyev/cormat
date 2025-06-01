#include "imgui.hpp"
#include "imgui.h"

void myGui::mainGui(camera &camera)
{
    ImVec2 windowSize(600, 300);
    ImGui::SetWindowSize(windowSize);
    ImGui::Begin("Control Panel");
    ImGui::SliderFloat("Walk speed", &camera.cameraSpeed, 0, 3);
    ImGui::End();
}

void myGui::initializeGui()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
}

void myGui::setupPlatform(glfwWindow glfwCamera)
{
    ImGui_ImplGlfw_InitForOpenGL(glfwCamera.window, true);
    ImGui_ImplOpenGL3_Init();
}

void myGui::startGuiFrames()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void myGui::renderGuiFrames()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void myGui::closeGui()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
