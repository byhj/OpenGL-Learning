#version 330 core

out vec4 color;
  
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform float ambientIntensity = 0.1;
uniform vec3 lightPos = vec3(1.0f, 0.5f, 1.0f);
uniform vec3 viewPos;

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

	//specular
	float specularIntensity = 0.5f;
	vec3 viewDir = normalize(viewPos - fs_in.FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
	vec3 specular = spec * specularIntensity * lightColor;

	//result
	vec3 result = ambient +diffuse + specular;
    color = vec4( result * objectColor, 1.0f);
}