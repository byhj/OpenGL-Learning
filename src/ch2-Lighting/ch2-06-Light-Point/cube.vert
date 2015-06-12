#version 330 core

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Normal;
layout (location = 2) in vec2 TexCoord;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;

out VS_FS
{
  vec3 view_pos;
  vec3 normal;
  vec2 tc;
}vs_out;

void main()
{
    mat4 mv = view * model;
	mat4 mvp = proj * mv;
	
	vs_out.view_pos = mat3(model) * Position;
	vs_out.normal   = mat3(transpose(inverse(model))) * Normal;
	vs_out.tc       = TexCoord;
    gl_Position = mvp * vec4(Position, 1.0f);
} 