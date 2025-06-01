#version 430 core
layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 color;
layout(location = 2) in vec2 texture;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 finalColor;
out vec2 textureCoord;

void main()
{
    gl_Position = projection * view * model * vec4(pos, 1.0f);
    textureCoord = texture;
    finalColor = color;
}
