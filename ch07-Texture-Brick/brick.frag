#version 330

layout (location = 0) out vec4 fragColor;
in vec2 tc;
uniform sampler2D brick;

void main()
{
	fragColor = texture2D(brick, tc);
}