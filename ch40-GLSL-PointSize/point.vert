#version 430 core

layout (location = 0) in vec3 Position;

void main()
{
   gl_Position = vec4(Position, 1.0f);
   gl_PointSize = 20.0f;
}