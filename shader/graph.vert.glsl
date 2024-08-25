#version 430 core
layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 finalColor;

void main()
{
    gl_Position = projection * view * model * vec4(pos, 1.0f);
    finalColor = color;
}