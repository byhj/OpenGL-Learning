#version 330 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 texcoord;

out VS_OUT
{
 vec2 tc;
}vs_out;

void main()
{
    gl_Position = vec4(position, 0.0, 1.0);
	vs_out.tc = texcoord;
}