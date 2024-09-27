#include "shader.hpp"
#include "glad.h"
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

shader::shader(const char* vertexFilePath, const char* fragmentFilePath)
{
    std::string vertexShaderSource = getFileSource(vertexFilePath);
    const char* cvertexShaderSource = vertexShaderSource.c_str();

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &cvertexShaderSource, NULL);
    glCompileShader(vertexShader);
    shader::checkErrors(vertexShader, false);

    // FIXME:
    // getFileSource has to be called one by one
    // otherwise it will overwrite source files
    // I couldn't debug this so it will stay like that.
    
    std::string fragmentShaderSource = getFileSource(fragmentFilePath);
    const char* cfragmentShaderSource = fragmentShaderSource.c_str();
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &cfragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    shader::checkErrors(fragmentShader, false);

    shaderProgramID = glCreateProgram();
    glAttachShader(shaderProgramID, vertexShader);
    glAttachShader(shaderProgramID, fragmentShader);
    glLinkProgram(shaderProgramID);
    shader::checkErrors(shaderProgramID, true);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}


shader::~shader(){}


// WARNING: the function is buggy, calling it twice in a row rewrites the first call
//          so, properly use the first function before calling it agian.
//FIXME: fix the warning

// A simple function to retrieve shader source code from a file to the main program.
std::string
shader::getFileSource(const char* filePath)
{
    std::string fileCode;
    std::ifstream fileFile;
    fileFile.exceptions( std::ifstream::failbit | std::ifstream::badbit);
    try 
    {
        fileFile.open(filePath);
        std::stringstream fileStream;
        fileStream << fileFile.rdbuf();
        fileFile.close();
        fileCode = fileStream.str();
    }
    catch (const std::ifstream::failure& e)
    {
        std::cout << "ERROR: Couldn't Retrieve " << filePath << "  \n" << e.what() << std::endl;
    }

    return fileCode;
}


void
shader::use()
{
    glUseProgram(shader::shaderProgramID);
}


void
shader::checkErrors(unsigned int shaderType, bool isProgram)
{
    if (isProgram == false)
    {
        int isCompiled = 0;
        glGetShaderiv(shaderType, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == 0)
        {
            int logLength = 0;
            glGetShaderiv(shaderType, GL_INFO_LOG_LENGTH, &logLength);

            std::vector<char> errorLog(static_cast<unsigned long>(logLength));
            glGetShaderInfoLog(shaderType, logLength, &logLength, &errorLog[0]);
            std::string str(errorLog.begin(), errorLog.end());
            std::cout << "ERROR: SHADER " << shaderType << " COMPILATION ERROR\n" << str << std::endl;
            return;
        }
    }
    else 
    {
        int isLinked = 0;
        glGetProgramiv(shaderType, GL_LINK_STATUS, &isLinked);
        if (isLinked == 0 )
        {
            int logLength = 0;
            glGetShaderiv(shaderType, GL_INFO_LOG_LENGTH, &logLength);

            std::vector<char> errorLog(static_cast<unsigned long>(logLength));
            glGetShaderInfoLog(shaderType, logLength, &logLength, &errorLog[0]);
            std::string str(errorLog.begin(), errorLog.end());

            std::cout << "ERROR: SHADER LINKING ERROR\n" << str << std::endl;
            return;
        }
    }
}


void
shader::updateModelM(double changeX, double changeY, float rotationSpeed)
{
    model = glm::mat4(1.0f);
    setMat4("model", model);
    model = glm::rotate(model, static_cast<float>(glm::radians(changeX)), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, static_cast<float>(glfwGetTime() * rotationSpeed), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, static_cast<float>(glm::radians(changeY)), glm::vec3(1.0f, 0.0f, 0.0f));
    setMat4("model", model);
}


void
shader::updateViewM(glm::vec3 cameraPosition, glm::vec3 cameraFront, glm::vec3 worldUp)
{
    view = glm::lookAt(cameraPosition, cameraPosition+ cameraFront, worldUp);
    setMat4("view",view);
}


void
shader::updateProjectionM(float fov)
{
    projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(fov), static_cast<float>(SCR_WIDTH) / static_cast<float>(SCR_HEIGHT), 0.1f, 100.0f);
    setMat4("projection", projection);
}


void    
shader::setInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(shaderProgramID, name.c_str()), value);
}


void
shader::setMat4(const std::string &name, const glm::mat4 &mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
