#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

out vec2 TexCoords;
out vec3 n;
out vec3 FragPos;

uniform mat4 mvp_matrix;
uniform mat4 model_matrix;


void main()
{
    gl_Position = mvp_matrix * vec4(position, 1.0f);
	n = mat3(model_matrix) * normal;
	FragPos = mat3(model_matrix)  * position;

    TexCoords = texCoords;
}