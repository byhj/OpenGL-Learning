#version 330

layout (location = 0) out vec4 fragColor;

in vec2 tc;

uniform sampler2D tex1;
uniform sampler2D tex2;

void main()
{
    fragColor = mix(texture(tex1, tc), texture(tex2, tc), 0.2);
}