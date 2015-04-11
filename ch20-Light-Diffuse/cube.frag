#version 330 core

out vec4 color;
  
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform float ambientIntensity = 0.5;
uniform vec3 lightPos = vec3(1.2f, 1.0f, 2.0f);

in VS_OUT {
   vec3 FragPos;
   vec3 Normal;
}fs_in;

void main()
{
    //ambient
	vec3 ambient = ambientIntensity * lightColor;
	//diffuse
    vec3 norm = normalize(fs_in.Normal);
	vec3 lightDir = normalize(lightPos - fs_in.FragPos);
	float diff = max( dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;
	//result
	vec3 result = ambient +diffuse;
    color = vec4( result * objectColor, 1.0f);
}