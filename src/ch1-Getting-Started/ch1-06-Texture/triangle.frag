#version 330 core

layout (location = 0) out vec4 fragColor;

in VS_OUT
{
  vec2 tc;
}fs_in;

uniform sampler2D tex;

void main()
{
    fragColor = texture(tex, fs_in.tc);
}