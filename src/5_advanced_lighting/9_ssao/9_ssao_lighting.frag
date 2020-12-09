#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedoSpec;
uniform sampler2D ssao;

struct Light
{
    vec3 Position;
    vec3 Color;

    float Linear;
    float Quadratic;
};

uniform Light light;

void main()
{
    vec3 FragPos = texture(gPosition, TexCoords).rgb;
    vec3 Normal = texture(gNormal, TexCoords).rgb;
    vec3 Diffuse = texture(gAlbedoSpec, TexCoords).rgb;
    float Specular = texture(gAlbedoSpec, TexCoords).r;
    float AmbientOcclusion = texture(ssao, TexCoords).r;

    vec3 ambient = vec3(0.3f * Diffuse * AmbientOcclusion);
    vec3 lighting = ambient;

    vec3 viewDir = normalize(FragPos);  // viewPos is (0, 0, 0);

    // diffuse
    vec3 lightDir = normalize(light.Position - FragPos);
    vec3 diffuse = max(dot(Normal, lightDir), 0.0f) * Diffuse * light.Color;

    // specular
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(Normal, halfwayDir), 0.0f), 8.0f);
    vec3 specular = light.Color * spec * Specular;

    // attenuation
    float distance = length(light.Position - FragPos);
    float attenuation = 1.0f / (1.0f + light.Linear * distance + light.Quadratic * distance * distance);
    diffuse *= attenuation;
    specular *= attenuation;
    lighting += diffuse + specular;

    FragColor = vec4(lighting, 1.0f);
}
