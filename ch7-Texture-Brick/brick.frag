#version 330

layout (location = 0) out vec4 fragColor;
in vec2 tc;
uniform sampler2D brick;

void main()
{
    vec4 cc = texture2D(brick, tc);
	fragColor = cc + vec4(1.0);
}