#version 330 core
out vec4 color;

struct Material {
   sampler2D diffuse;
   sampler2D specular;
   float shininess;
};
struct Light {
   vec3 position;
   vec3 ambient;
   vec3 diffuse;
   vec3 specular;
   vec3 direction;
   float cutOff;
   float constant;
   float linear;
   float quadratic;
};

uniform Light light;
uniform Material material;
in vec3 n;
vec3 lightPos = vec3(1.2, 1.0, 2.0);
vec3 viewPos = vec3(0.0, 0.0, 3.0);
in vec3 FragPos;
in vec2 tc;

void main()
{
	vec3 lightDir = normalize(lightPos - FragPos);
	float theta = dot(lightDir, normalize(-light.direction));
	if (theta > light.cutOff) {
//ambient
   vec3 ambient = light.ambient * vec3(texture(material.diffuse, tc));
//diffuse
    vec3 norm = normalize(n);

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, tc));  
//specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular, tc));
   // Attenuation
    float dis   = length(lightPos - FragPos);
    float attenuation = 1.0f / (light.constant + light.linear * dis + light.quadratic * (dis * dis));    

     // ambient  *= attenuation;  // Also remove attenuation from ambient, because if we move too far, the light in spotlight would then be darker than outside (since outside spotlight we have ambient lighting). 
    diffuse  *= attenuation;
    specular *= attenuation;   
    vec3 result = (ambient + diffuse +  specular);
    color = vec4(result, 1.0f);
	} //if
    else    // else, use ambient light so scene isn't completely dark outside the spotlight.
       color = vec4(light.ambient * vec3(texture(material.diffuse,tc)), 1.0f);
}