#include "imgui.hpp"
#include "imgui.h"

void myGui::mainGui(camera &camera, graph &graph)
{
    ImVec2 windowSize(600, 300);
    ImGui::SetWindowSize(windowSize);
    ImGui::Begin("Graph Control");
    ImGui::SliderFloat("Rotation speed", &camera.cameraRotationSpeed, 0, 3);
    ImGui::SliderFloat("Walk speed", &camera.cameraSpeed, 0, 3);

    float x = camera.cameraRotationSpeed;
    static int clickedRotateButton = 0;
    if (ImGui::Button("Stop/Start rotating"))
        clickedRotateButton++;
    if (clickedRotateButton & 1)
    {
        ImGui::SameLine();
        camera.cameraRotationSpeed = 0;
    }
    else
        camera.cameraRotationSpeed = x;

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
