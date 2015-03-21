#version 330

layout (location = 0) in vec3 position;
out vec4 vColor;

void main()
{
    vColor = vec4(0.5f, 0.0f, 0.0f, 1.0f);
    gl_Position = vec4(position, 1.0);
}