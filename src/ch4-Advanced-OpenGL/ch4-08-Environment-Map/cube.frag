#version 330

layout (location = 0) out vec4 fragColor;

in vec3 Normal;
in vec3 FragPos;

uniform samplerCube skybox;
uniform vec3 cameraPos = vec3(0.0, 0.0, 3.0);

void main()
{
    vec3 I = normalize(FragPos - cameraPos);
    vec3 R = reflect(I, normalize(Normal));

     fragColor = texture(skybox, R);
}