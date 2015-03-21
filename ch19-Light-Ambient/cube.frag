#version 330 core

out vec4 color;
  
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform float ambientIntensity = 0.5;

void main()
{
    vec3 ambient = ambientIntensity * lightColor;
    color = vec4(ambient * objectColor, 1.0f);
}