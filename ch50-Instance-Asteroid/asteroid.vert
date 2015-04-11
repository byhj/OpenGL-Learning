#version 330 core

layout (location = 0) in vec3 position;
layout (location = 2) in vec2 texCoords;
layout (location = 3) in mat4 instanceMatrix;

out vec2 TexCoords;

uniform mat4 mvp;

void main()
{
    gl_Position = mvp * instanceMatrix * vec4(position, 1.0f); 
    TexCoords = texCoords;
}