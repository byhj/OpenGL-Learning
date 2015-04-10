#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

uniform mat4 mvp_matrix;
uniform mat4 model_matrix;
out vec3 n;
out vec3 FragPos;

void main()
{
    FragPos = position;
    gl_Position = mvp_matrix * vec4(position, 1.0f);
	n = mat3(model_matrix) * normal;
} 