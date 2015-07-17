#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

out vec3 n;
out vec3 FragPos;
out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

out VS_OUT {
    vec3 normal;
} vs_out;

void main()
{

    mat4 mvp = proj * view * model;


    TexCoords = texCoords;
	vs_out.normal = mat3( transpose( inverse(model) ) ) * normal;
	FragPos = mat3(model)  * position;

	gl_Position = mvp * vec4(position, 1.0f);
}