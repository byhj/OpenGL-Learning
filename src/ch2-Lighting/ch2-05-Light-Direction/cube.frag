#version 330 core

out vec4 fragColor;
  
 struct Material 
{
  sampler2D diffuse;
  sampler2D specular;
  float shininess;
};

struct Light {
   vec3 position;
   vec3 ambient;
   vec3 diffuse;
   vec3 specular;
};

in VS_FS
{
  vec3 view_pos;
  vec3 normal;
  vec2 tc;
}fs_in;

uniform Material material;
uniform Light light;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
    vec3 normal   = normalize(fs_in.normal);

    //ambient
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, fs_in.tc));

	//diffuse
	vec3 lightDir = normalize(lightPos - fs_in.view_pos);
	float diff    = max( dot(normal, lightDir), 0.0);
	vec3 diffuse  = diff * light.diffuse * vec3(texture(material.diffuse, fs_in.tc));

	//specular
	float shininess = 64.0f;
	vec3 viewDir    = normalize(viewPos - fs_in.view_pos);
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec      = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular   = spec * light.specular * vec3(texture(material.specular, fs_in.tc));

	//result
	vec3 result = ambient + diffuse + specular;
    fragColor = vec4(result, 1.0f);
}