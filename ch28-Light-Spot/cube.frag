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

   vec3 ambient;
   vec3 diffuse;
   vec3 specular;

   float constant;
   float linear;
   float quadratic;
};

uniform Material material;
uniform Light light;
uniform vec3 lightPos = vec3(1.2f, 1.0f, 2.0f);
uniform vec3 viewPos;

in VS_OUT {
   vec3 FragPos;
   vec3 Normal;
   vec2 tc;
}fs_in;

void main()
{
	vec3 lightDir = normalize(light.position - fs_in.FragPos);
    // Check if lighting is inside the spotlight cone
    float theta = dot(lightDir, normalize(-light.direction)); 
    if(theta > light.cutOff) // Remember that we're working with angles as cosines instead of degrees so a '>' is used.
    {  
    //ambient
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, fs_in.tc));
	//diffuse
    vec3 norm = normalize(fs_in.Normal);

	float diff = max( dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * light.diffuse * vec3(texture(material.diffuse, fs_in.tc));

	//specular
	vec3 viewDir = normalize(viewPos - fs_in.FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = spec * light.specular * vec3(texture(material.specular, fs_in.tc));;
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
    else    // else, use ambient light so scene isn't completely dark outside the spotlight.
        fragColor = vec4(light.ambient * vec3(texture(material.diffuse, fs_in.tc)), 1.0f);

}