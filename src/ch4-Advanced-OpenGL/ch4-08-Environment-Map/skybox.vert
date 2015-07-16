#version 430 core

layout (location = 0) in vec3 Position;

out vec3 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
    mat4 mvp  = proj * view * model;
    vec4 pos = mvp * vec4(Position, 1.0f);
	TexCoords = Position;

	//Set the z depth value to 1.0f for most far
	gl_Position = pos.xyww;
 }
