#version 330

layout (location = 0) out vec4 fragColor;

in vec2 tc;
in vec3 vColor;
uniform sampler2D container;

void main()
{
    fragColor =  texture2D(container, tc) * vec4(vColor, 1.0);
}