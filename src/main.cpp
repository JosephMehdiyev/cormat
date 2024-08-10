#include "glad.h"
#include "glfw3.h"

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
    graph graph(20);

    while (!glfwWindowShouldClose(glfwCamera.window))
    {
        glfwCamera.processInput();
        graph.start(glfwCamera);
        glfwCamera.swapBuffers();
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
