#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
uniform mat4 mvp;
uniform mat4 model;

out VS_OUT {
  vec3 FragPos;
  vec3 Normal;
}vs_out;

void main()
{
    gl_Position = mvp * vec4(position, 1.0f);
    vs_out.FragPos = mat3(model) * position;
	vs_out.Normal =  mat3(model) * normal;
} 