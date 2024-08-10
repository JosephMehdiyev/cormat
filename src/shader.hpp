#pragma once 

#include <string>
#include <glm/glm.hpp>


const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

class shader
{
public:
    shader(const char* vertexFilePath, const char* fragmentFilePath);
    ~shader();
    void use();
    void setMat4(const std::string &name, const glm::mat4 &mat) const;
    void setInt(const std::string &name, int value) const;
    unsigned int vertexShader, fragmentShader, shaderProgramID;
    void updateProjectionM(float fov);
    void updateModelM(double changeX, double changeY);
    void updateViewM(glm::vec3 cameraPosition, glm::vec3 cameraFront, glm::vec3 worldUp);
    glm:: mat4 model, view, projection;
private:
    // Returns a C-style string with input file directory path.
    // REMARK: you must fully use the return file before recalling this function.
    // otherwise the new return file will overload the old return file
    const char* getFileSource(const char* filePath);
    // Checks errors for shader linking and compilations
    // If it is a shader program, bool must be TRUE, if it is a shader (compilation), then FALSE
    void checkErrors(unsigned int shaderType, bool isProgram);
};
