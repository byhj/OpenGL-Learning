#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;

out vec2 tc;
out vec3 vColor;
uniform mat4 transform;

void main()
{
   gl_Position = transform * vec4(position, 1.0f);
   tc = texCoord;
   vColor = color;
}