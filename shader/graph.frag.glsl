#version 430 core
out vec4 fragColor;

uniform sampler2D TEXTURE_EXAMPLE;
in vec3 finalColor;
in vec2 textureCoord;
void main()
{
    fragColor = texture(TEXTURE_EXAMPLE, textureCoord);
}
