#version 330 core

out vec4 fragColor;

 struct Material {
  sampler2D diffuse;
  sampler2D specular;
  float shininess;
};

struct Light {
   vec3 position;
   vec3 direction;
   float cutOff;
   float outerCutOff;

   vec3 ambient;
   vec3 diffuse;
   vec3 specular;

   float constant;
   float linear;
   float quadratic;
};

uniform Material material;
uniform Light light;
uniform vec3 viewPos;

in VS_OUT {
   vec3 FragPos;
   vec3 Normal;
   vec2 tc;
}fs_in;

void main()
{

    //ambient
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, fs_in.tc));

	//diffuse
    vec3 norm = normalize(fs_in.Normal);
	vec3 lightDir = normalize(light.position - fs_in.FragPos);
	float diff = max( dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * light.diffuse * vec3(texture(material.diffuse, fs_in.tc));

	//specular
	vec3 viewDir = normalize(viewPos - fs_in.FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = spec * light.specular * vec3(texture(material.specular, fs_in.tc));;
	
	// Spotlight (soft edges)
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = (light.cutOff - light.outerCutOff);
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    diffuse  *= intensity;
    specular *= intensity;

	//atten
	float dis = length(light.position - fs_in.FragPos);
    float attenuation = 1.0f / (light.constant + light.linear * dis + light.quadratic * (dis * dis));   
	
	//result
	ambient  *= attenuation; 
    diffuse  *= attenuation;
    specular *= attenuation; 
	vec3 result = ambient + diffuse + specular;
    fragColor = vec4(result, 1.0f);
}