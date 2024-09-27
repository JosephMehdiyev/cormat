#include "imgui.hpp"

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
