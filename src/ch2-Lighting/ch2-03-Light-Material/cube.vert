#version 330 core

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Normal;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;

out VS_FS
{
  vec3 view_pos;
  vec3 normal;
}vs_out;

void main()
{
    mat4 mv = view * model;
	mat4 mvp = proj * mv;

	vs_out.view_pos = mat3(mv) * Position;
	vs_out.normal   = mat3(mv) * Normal;
	 
    gl_Position = mvp * vec4(Position, 1.0f);
} 