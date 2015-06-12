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

uniform mat4 transform;

void main()
{
   vs_out.tc = VertexData[gl_VertexID].xy + vec2(0.5f, 0.5f);

   //SOIL load the texture (0, 0) is on the left top
   vs_out.tc.y = 1.0f - vs_out.tc.y;

   gl_Position = transform * VertexData[gl_VertexID];
}