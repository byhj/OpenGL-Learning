#version 330 core

layout (location = 0) in vec3 position;

uniform mat4 mvp;
uniform vec3 color;

out vec3 vColor;

void main()
{
    gl_Position = mvp * vec4(position, 1.0f);
	vColor = color;
} 