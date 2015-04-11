#version 330 core

out vec4 fragColor;
 
 struct Material {
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  float shininess;
};

struct Light {
   vec3 position;
   vec3 ambient;
   vec3 diffuse;
   vec3 specular;
};

uniform Material material;
uniform Light light;
uniform vec3 lightPos = vec3(1.0f, 0.5f, 1.0f);
uniform vec3 viewPos;

in VS_OUT {
   vec3 FragPos;
   vec3 Normal;
}fs_in;

void main()
{
    //ambient
	vec3 ambient = material.ambient * light.ambient;

	//diffuse
    vec3 norm = normalize(fs_in.Normal);
	vec3 lightDir = normalize(lightPos - fs_in.FragPos);
	float diff = max( dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * material.diffuse * light.diffuse;

	//specular
	vec3 viewDir = normalize(viewPos - fs_in.FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = spec * material.specular * light.specular;

	//result
	vec3 result = ambient + diffuse + specular;
    fragColor = vec4(result, 1.0f);
}