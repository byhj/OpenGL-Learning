#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

out vec3 Normal;
out vec3 WorldPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{

    mat4 mvp  = proj * view * model;

	Normal = mat3( transpose( inverse(model) ) ) * normal;
	WorldPos = vec3(model * vec4(position, 1.0f));

    gl_Position = mvp * vec4(position, 1.0f);
}

 