#include "glad.h"
#include "glfw3.h"

#include "shader.hpp"
#include "glfwCamera.hpp"

#include "texture.hpp"
#include "render.hpp"
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// settings





// THIS IS AN INITIALIZATION FILE, NOT INTENDED FOR PRODUCTION IN ANY MEANS
// THE SOURCE CODE BELOW IS A INTRODUCTORY OPENGL TRIANGLE CODE FROM LEARNOPENGL
// THIS CODE IS TEMPORARY

int main()
{
    glfwCamera glfwCamera(SCR_WIDTH, SCR_HEIGHT);
    render render;
    Texture texture1("../data/textures/dark.png");
    shader shader("../shader/basic.vert.glsl", "../shader/basic.frag.glsl");






    // render loop
    // -----------
    while (!glfwWindowShouldClose(glfwCamera.window))
    {   
        glfwCamera.processInput();
        
        //TODO: change the rendering structure for a better, cleaner one.
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        shader.use();
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        //TODO: currently the matrix generation is a mess, it should be rewritten.
        shader.initializeProjectionM();
        shader.updateProjectionM(glfwCamera.fov);
        shader.updateViewM(glfwCamera.cameraPosition, glfwCamera.cameraFront, glfwCamera.worldUp);
        shader.updateModelM(glfwCamera.changeInX, glfwCamera.changeInY);
        

        //TODO:  same as the first TODO, rendering structure must be changed, really.
        glBindVertexArray(render.VAO); 
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwCamera.swapBuffers();
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
