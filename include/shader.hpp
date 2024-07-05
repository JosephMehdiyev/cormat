#pragma once 

#include "glad.h"
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>


const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

class shader
{
public:
    shader(const char* vertexFilePath, const char* fragmentFilePath);
    void use();
    void setMat4(const std::string &name, const glm::mat4 &mat) const;
    void setInt(const std::string &name, int value) const;
    unsigned int vertexShader, fragmentShader, shaderProgramID;
    void initializeModelM();
    void initializeViewM();
    void initializeProjectionM();
    glm:: mat4 model, view, projection;

private:
    const char* getFileSource(const char* filePath);
    void checkErrors(unsigned int shaderType, bool isProgram);
};