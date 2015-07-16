#version 430 core

uniform sampler2D sprite_texture;

out vec4 fragColor;

void main(void)
{

   vec4 texColor =  texture(sprite_texture, vec2(gl_PointCoord.x, 1.0 - gl_PointCoord.y));
   	//alpha < 0.1 discard
    if(texColor.a < 0.5f)
        discard;

   fragColor = texColor;
}