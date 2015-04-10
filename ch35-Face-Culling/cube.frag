#version 330

layout (location = 0) out vec4 fragColor;

in vec2 tc;

uniform sampler2D tex1;
uniform sampler2D tex2;

void main()
{
   if(gl_FrontFacing)
     fragColor = vec4(1.0f);
   else
     fragColor = vec4(0.0, 1.0, 0.0, 0.0);
   //   fragColor = mix(texture(tex1, tc), texture(tex2, tc), 0.2);
}