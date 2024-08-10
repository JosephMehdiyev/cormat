#include "glad.h"
#include "glfw3.h"

#include "shader.hpp"
#include "glfwCamera.hpp"

#include "texture.hpp"
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "graph.hpp"

int main()
{
    glfwCamera glfwCamera(SCR_WIDTH, SCR_HEIGHT);
    shader shader("../shader/graph.vert.glsl", "../shader/graph.frag.glsl");
    graph graph(20);

    while (!glfwWindowShouldClose(glfwCamera.window))
    {   
        glfwCamera.processInput();
       
        //TODO: change the rendering structure for a better, cleaner one.
        glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
        shader.use();
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //TODO: currently the matrix generation is a mess, it should be rewritten.
        shader.updateProjectionM(glfwCamera.fov);
        shader.updateViewM(glfwCamera.cameraPosition, glfwCamera.cameraFront, glfwCamera.worldUp);
        shader.updateModelM(glfwCamera.changeInX, glfwCamera.changeInY);
        

        //TODO:  same as the first TODO, rendering structure must be changed, really.
        graph.draw();

        glfwCamera.swapBuffers();
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
