#pragma once 

#include "glad.h"
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>

class shader
{
public:
    shader(const char* vertexFilePath, const char* fragmentFilePath);
    void use();
private:
    const char* getFileSource(const char* filePath);
    void checkErrors(unsigned int shaderType, bool isProgram);
    unsigned int vertexShader, fragmentShader, shaderProgramID;
};