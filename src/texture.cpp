#include "texture.hpp"
#include "glad.h"
#include "stb_image.hpp"
#include <GL/gl.h>
#include <iostream>
#include <stdexcept>

// TODO: feature to support more than 1 textures at a time.
//       also calling the class twice is buggy(?).
void texture::generateTexture()
{
    glGenTextures(1, &Texture);
    glBindTexture(GL_TEXTURE_2D, Texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void texture::loadTexture(const char *textureFileLocation)
{
    int width, height, nrChannels;
    unsigned char *data = stbi_load(textureFileLocation, &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        throw std::runtime_error("ERROR: COULDN'T LOAD THE TEXTURE");
    }
    stbi_image_free(data);
}

void texture::bindTexture()
{
    glBindTexture(GL_TEXTURE_2D, Texture);
}

texture::texture(const char *textureFilePath)
{
    texture::generateTexture();
    texture::loadTexture(textureFilePath);
}

texture::~texture()
{
}
