#version 330 core
out vec4 color;
  
uniform vec3 objectColor;
uniform vec3 lightColor;
in vec3 n;
vec3 lightPos = vec3(1.2f, 0.5f, 1.0f);
in vec3 fragPos;

void main()
{
    vec3 norm = normalize(n);
	vec3 lightDir = normalize(lightPos - fragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;
    float ambientStrength = 0.5f;
    vec3 ambient = ambientStrength * lightColor;
    vec3 result = (ambient + diffuse) * objectColor;
    color = vec4(result, 1.0f);
}