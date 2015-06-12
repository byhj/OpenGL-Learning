#version 330 core

layout (location = 0) in vec3 Position;
layout (location = 1) in vec2 texCoords;

out vec2 tc;

void main(void)
{
   tc = texCoords;
   gl_Position = vec4(Position, 1.0f);
}