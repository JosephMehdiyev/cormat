#pragma once

class Texture
{
public:
    // Input the file directory path to construct a texture
    Texture(const char* textureFilePath);
    ~Texture();
    // Bind the texture for rendering purposes
    void bindTexture();
    unsigned int texture;
private:
    void generateTexture();
    // loads the texture data ( for example png and jpg files) with stbi library.
    // And sents it into OpenGL
    void loadTexture(const char* textureFileLocation);
};