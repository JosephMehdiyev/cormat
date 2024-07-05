#pragma once

class Texture
{
public:
    Texture(const char* textureFilePath);
    ~Texture();
    void bindTexture();
    unsigned int texture;
private:
    void generateTexture();
    void loadTexture(const char* textureFileLocation);
};