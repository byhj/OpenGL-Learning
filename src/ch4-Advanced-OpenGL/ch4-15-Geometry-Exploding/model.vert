#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

out VS_OUT {
    vec2 TexCoords;
} vs_out;

out vec3 n;
out vec3 FragPos;

uniform mat4  model;
uniform mat4  view;
uniform mat4  proj;


void main()
{
    mat4 mvp = proj * view * model;

	vs_out.TexCoords = texCoords;
	n = mat3( transpose( inverse(model) ) ) * normal;
	FragPos = mat3(model)  * position;

    gl_Position = mvp * vec4(position, 1.0f);
}