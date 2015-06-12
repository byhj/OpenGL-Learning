#version 330 core

in VS_FS
{
  vec3 FragPos;
  vec3 normal;
  vec2 TexCoords;
}fs_in;

out vec4 fragColor;

struct Material 
{
   vec3 specular;
   sampler2D texture_diffuse1;
   sampler2D texture_specular1;
   float shininess;
};

struct Light {
   vec3 ambient;
   vec3 diffuse;
   vec3 specular;
};

uniform Light light;
uniform Material material;
vec3 lightPos = vec3(1.0f, -7.0f, 50.0f);
vec3 viewPos = vec3(0.0, 0.0, 10.0);

void main()
{    
//ambient
   vec3 ambient = light.ambient * vec3(texture2D(material.texture_diffuse1, fs_in.TexCoords));

//diffuse
    vec3 norm     = normalize(fs_in.normal);
	vec3 lightDir = normalize(lightPos - fs_in.FragPos);
	float diff    = max(dot(norm, lightDir), 0.0);
	vec3 diffuse  = light.diffuse * diff * vec3(texture2D(material.texture_diffuse1, fs_in.TexCoords));  

//specular
    vec3 viewDir    = normalize(viewPos - fs_in.FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec      = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular   =  light.specular * spec * vec3(texture2D(material.texture_specular1, fs_in.TexCoords));

// calc the all light attribute
    vec3 result = (ambient + diffuse + specular);
	fragColor = vec4(result, 1.0);
}
