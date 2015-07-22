#version 330

layout (location = 0) out vec4 fragColor;

in vec3 Normal;
in vec3 WorldPos;

uniform samplerCube skybox;
uniform vec3 cameraPos = vec3(0.0f, 1.0f, 3.0f);

void main()
{
    float ratio = 1.00 / 1.52;
    vec3 I = normalize(WorldPos - cameraPos);
    vec3 R = refract(I, normalize(Normal), ratio);

    fragColor = texture(skybox, R);
}