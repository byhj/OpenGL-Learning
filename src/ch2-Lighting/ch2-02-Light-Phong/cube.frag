#version 330 core

out vec4 fragColor;
  
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

in VS_FS
{
  vec3 view_pos;
  vec3 normal;
}fs_in;

void main()
{
    vec3 normal   = normalize(fs_in.normal);

    //ambient
	float ambientIntensity = 0.3f;
	vec3 ambient = ambientIntensity * lightColor;

	//diffuse
	float diffuseIntensity = 0.5f;
	vec3 lightDir = normalize(lightPos - fs_in.view_pos);
	float diff    = max( dot(normal, lightDir), 0.0);
	vec3 diffuse  =  diffuseIntensity * diff * lightColor;

	//specular
	float specularIntensity = 0.5f;
	float shininess = 64.0f;
	vec3 viewDir    = normalize(viewPos - fs_in.view_pos);
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec      = pow( max ( dot(viewDir, reflectDir), 0.0),  shininess);
	vec3 specular   = spec * specularIntensity * lightColor;

	//result
	vec3 result = ambient + diffuse + specular;
    fragColor = vec4(result * objectColor, 1.0f);
}