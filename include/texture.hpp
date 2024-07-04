#pragma once

class Texture
{
public:
    Texture(const char* textureFilePath);
    unsigned int texture;
private:
    void generateTexture();
    void loadTexture(const char* textureFileLocation);
    void parameters();
    void bindTexture();
};