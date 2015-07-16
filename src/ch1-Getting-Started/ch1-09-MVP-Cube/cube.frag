#version 330

layout (location = 0) out vec4 fragColor;

in vec2 tc;

uniform sampler2D faceTex;
uniform sampler2D contaninerTex;

void main()
{
    fragColor = mix( texture(contaninerTex, tc), texture(faceTex, tc), 0.2);
}