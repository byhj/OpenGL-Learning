#version 430 core

const vec3 VertexData[] = 
{
	vec3(  0.0f,  0.0f,  0.0f),
	vec3(  0.5f,  0.5f,  0.0f),
	vec3( -0.5f,  0.5f,  0.0f),
	vec3(  0.5f, -0.5f,  0.0f),
	vec3( -0.5f, -0.5f,  0.0f),
};

void main()
{
   gl_Position = vec4(VertexData[gl_VertexID], 1.0f);
}