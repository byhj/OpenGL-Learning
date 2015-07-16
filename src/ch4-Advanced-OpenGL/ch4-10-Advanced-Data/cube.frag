#version 330

layout (location = 0) out vec4 fragColor;

in vec2 tc;

uniform sampler2D containerTex;
uniform sampler2D faceTex;

void main()
{
    fragColor = mix(texture(containerTex, tc), texture(faceTex, tc), 0.2);
}