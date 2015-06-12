#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texcoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

out VS_OUT {
  vec3 FragPos;
  vec3 Normal;
  vec2 tc;
}vs_out;

void main()
{
    mat4 mvp = proj * view * model;
    gl_Position = mvp * vec4(position, 1.0f);
    vs_out.FragPos = mat3(model) * position;
	vs_out.Normal = mat3(transpose(inverse(model))) * normal;
	vs_out.tc = texcoord;
} 