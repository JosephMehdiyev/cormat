#pragma once

class texture
{
  public:
    // Input the file directory path to construct a texture
    texture(const char *textureFilePath);
    ~texture();
    // Bind the texture for rendering purposes
    void bindTexture();
    unsigned int Texture;

  private:
    void generateTexture();
    // loads the texture data ( for example png and jpg files) with stbi library.
    // And sents it into OpenGL
    void loadTexture(const char *textureFileLocation);
};
