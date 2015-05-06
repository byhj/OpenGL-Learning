#version 430 core

layout (location = 0) out vec4 fragColor;  //Æ¬ÔªÑÕÉ«

void main()
{ 
    if(gl_FrontFacing)
        fragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
    else
        fragColor = vec4(0.0f, 1.0f, 0.0f, 1.0f);   
}