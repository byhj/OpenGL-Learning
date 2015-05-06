#version 330

layout (location = 0) out vec4 fragColor;

in vec2 tc;

uniform sampler2D tex1;
uniform sampler2D tex2;

void main()
{
    fragColor = vec4(0.0, 1.0, 0.0, 1.0);
}