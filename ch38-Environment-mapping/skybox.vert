#version 430 core

layout (location = 0) in vec3 Position;

out vec3 TexCoords;

uniform mat4 mvp_matrix;

void main()
{
    gl_Position = mvp_matrix * vec4(Position, 1.0);
    TexCoords = Position;
 }