#version 430 core

layout (location = 0) out vec4 fragColor;

in VS_OUT
{
  vec2 tc;
}fs_in;

uniform sampler2D tex1;
uniform sampler2D tex2;

void main()
{
    fragColor = mix(texture(tex1, fs_in.tc) , texture(tex2, fs_in.tc), 0.2);
}