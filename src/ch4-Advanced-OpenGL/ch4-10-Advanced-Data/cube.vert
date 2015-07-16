#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;

out vec2 tc;

uniform mat4 mvp;

void main()
{
   gl_Position = mvp* vec4(position, 1.0f);
   tc = vec2(texCoord.x, 1.0 - texCoord.y);
}