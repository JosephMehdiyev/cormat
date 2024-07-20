#version 460 core
layout (location = 0) in vec3 position;


uniform mat4 view;
uniform mat4 projection;

out vec3 nearPoint;
out vec3 farPoint;

vec3 UnprojectPoint(float x, float y, float z, mat4 vieww, mat4 project) 
{
    mat4 viewInv = inverse(vieww);
    mat4 projInv = inverse(project);
    vec4 unprojectedPoint =  viewInv * projInv * vec4(x, y, z, 1.0);
    return unprojectedPoint.xyz / unprojectedPoint.w;
}


void main()
{
    nearPoint = UnprojectPoint(position.x, position.y, 0.0, view, projection).xyz; 
    farPoint = UnprojectPoint(position.x, position.y, 1.0, view, projection).xyz;
    gl_Position = vec4(position, 1.0);
}