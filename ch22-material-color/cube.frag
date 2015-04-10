#version 330 core
out vec4 color;

struct Material {
   vec3 ambient;
   vec3 diffuse;
   vec3 specular;
   float shininess;
};
struct Light {
   vec3 ambient;
   vec3 diffuse;
   vec3 specular;
};
uniform Light light;
uniform Material material;
in vec3 n;
vec3 lightPos = vec3(1.0, 0.5, 1.2);
vec3 viewPos = vec3(0.0, 0.0, 3.0);
in vec3 FragPos;

void main()
{
//ambient
    vec3 ambient = material.ambient * light.ambient;
//diffuse
    vec3 norm = normalize(n);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * (diff * material.diffuse) ;
//specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular =  light.specular * (spec * material.specular);  

    vec3 result = (ambient + diffuse +  specular);
    color = vec4(result, 1.0f);
}