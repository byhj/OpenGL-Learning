#version 430 core

layout (location = 0) in vec3 position;

//Ubo (index - binding - ubo)
layout (std140, binding = 0) uniform Transform
{
    mat4 proj;
    mat4 view;
};

uniform mat4 model;

void main()
{
    gl_Position = proj * view * model * vec4(position, 1.0);
}  