#version 430 core

layout (location = 0) out vec4 fragColor;

in VS_OUT
{
  vec2 tc;
}fs_in;

uniform sampler2D containerTex;
uniform sampler2D faceTex;

void main()
{
    fragColor = mix(texture(containerTex, fs_in.tc) , texture(faceTex, fs_in.tc), 0.2);
}