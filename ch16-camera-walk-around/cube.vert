#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;

out vec2 tc;
out vec3 vColor;
uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 proj_matrix;

void main()
{
   mat4  mvp_matrix = proj_matrix * view_matrix * model_matrix;
   gl_Position = mvp_matrix * vec4(position, 1.0f);
   tc = texCoord;
}