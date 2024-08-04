#version 430 core
out vec4 fragColor;

in vec3 finalColor;

void main()
{
    fragColor = vec4(finalColor, 1.0f);
}

