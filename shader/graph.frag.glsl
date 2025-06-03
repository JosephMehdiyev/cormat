#version 430 core
out vec4 fragColor;

uniform sampler2D TEXTURE_EXAMPLE;
uniform bool useTexture;
in vec3 finalColor;
in vec2 textureCoord;

void main()
{
    if (useTexture)
        fragColor = texture(TEXTURE_EXAMPLE, textureCoord);
    else
        fragColor = vec4(finalColor, 1.0);
}
