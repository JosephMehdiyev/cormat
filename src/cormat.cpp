#include "glad.h"
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "glfwCamera.hpp"

//#include "texture.hpp"
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "graph.hpp"

int main()
{
    glfwCamera glfwCamera(SCR_WIDTH, SCR_HEIGHT);
    graph graph(200);
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    
    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(glfwCamera.window, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
    ImGui_ImplOpenGL3_Init();

    while (!glfwWindowShouldClose(glfwCamera.window))
    {
        // (Your code calls glfwPollEvents())
        // ...
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::ShowDemoWindow(); // Show demo window! :)
        glfwCamera.processInput();
        graph.start(glfwCamera);
        glfwCamera.swapBuffers();
        glfwPollEvents();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
    glfwTerminate();
    return 0;
}
