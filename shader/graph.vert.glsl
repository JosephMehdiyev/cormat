#version 430 core
layout(location = 0) in vec3 posData;
layout(location = 1) in vec3 colorData;
layout(location = 2) in vec2 textureData;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 finalColor;
out vec2 textureCoord;

void main()
{
    gl_Position = projection * view * model * vec4(posData, 1.0f);
    textureCoord = textureData;
    finalColor = colorData;
}
