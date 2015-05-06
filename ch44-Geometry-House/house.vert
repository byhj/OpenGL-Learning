#version 430 core

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 color;

out VS_OUT {
    vec3 color;
} vs_out;

void main()
{
   gl_Position = vec4(Position, 1.0f);
   vs_out.color = color;
}