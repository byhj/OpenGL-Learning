#version 430 core

const vec4 VertexData[4] = {
                             vec4(-0.5f, -0.5f, 0.0f, 1.0f), 
							 vec4( 0.5f, -0.5f, 0.0f, 1.0f),
							 vec4(-0.5f,  0.5f, 0.0f, 1.0f),
							 vec4( 0.5f,  0.5f, 0.0f, 1.0f),
							};
out VS_OUT
{
  vec2 tc;
}vs_out;

void main()
{
   vs_out.tc = VertexData[gl_VertexID].xy + vec2(0.5f, 0.5f);
   gl_Position = VertexData[gl_VertexID];
}