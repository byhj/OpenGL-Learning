#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

out vec3 n;
out vec3 FragPos;
out vec2 TexCoords;

uniform mat4 mvp_matrix;
uniform mat4 model_matrix;

out VS_OUT {
    vec3 normal;
} vs_out;

void main()
{
    gl_Position = mvp_matrix * vec4(position, 1.0f);
    TexCoords = texCoords;
	n = mat3(model_matrix) * normal;
	vs_out.normal = n;
	FragPos = mat3(model_matrix)  * position;
}