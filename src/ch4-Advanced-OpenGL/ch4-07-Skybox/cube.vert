#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;

out vec2 tc;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
    tc = vec2(texCoord.x, 1.0 - texCoord.y);

    mat4 mvp  = proj * view * model;
    gl_Position = mvp * vec4(position, 1.0f);
}

