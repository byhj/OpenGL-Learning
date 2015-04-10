#version 130
//#version 330 core
out vec4 color;
  
uniform vec3 objectColor;
uniform vec3 lightColor;
varying vec3 n;
vec3 lightPos = vec3(1.2, 0.5, 1.0);
vec3 viewPos = vec3(0.0, 0.0, 3.0);
varying vec3 FragPos;

void main()
{
	vec3 lightDir = normalize(lightPos - FragPos);
    float specularStrength = 0.5f;
    vec3 norm = normalize(n);
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;  

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * lightColor;
    vec3 result = (ambient + diffuse +  specular) * objectColor;
    color = vec4(result, 1.0f);
}