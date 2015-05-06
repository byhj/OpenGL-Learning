#version 330 core

in vec2 TexCoords;
in vec3 n;
in vec3 FragPos;
out vec4 color;

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
vec3 lightPos = vec3(1.0f, -7.0f, -15.0f);
vec3 viewPos = vec3(0.0, 0.0, 10.0);

void main()
{    
//ambient
   vec3 ambient = light.ambient * vec3(texture2D(material.texture_diffuse1, TexCoords));

//diffuse
    vec3 norm = normalize(n);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * diff * vec3(texture2D(material.texture_diffuse1, TexCoords));  

//specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular =  light.specular * spec ; //* vec3(texture2D(material.texture_specular1, TexCoords));

// calc the all light attribute
    vec3 result = (ambient + diffuse);
	color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}
