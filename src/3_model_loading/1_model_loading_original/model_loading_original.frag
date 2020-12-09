#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec2 TexCoords;
in vec3 Normal;

struct Material
{
    sampler2D texture_diffuse1;
    sampler2D texture_specular1;
    sampler2D texture_normal1;
};

uniform Material material;
uniform vec3 viewPos;
uniform vec3 lightDir;

void main()
{
    vec3 diffColor = texture(material.texture_diffuse1, TexCoords).rgb;
    vec3 specColor = texture(material.texture_diffuse1, TexCoords).rrr;

    // ambient
    vec3 ambient = 0.1f * diffColor;  // ambient_strength * object_color

    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightDir);
    float diff = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse = 0.6f * (diff * diffColor);  // diffuse_strength * object_color

    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32.0f);
    vec3 specular = 1.0f * (spec * specColor);  // specular_strength * object_color

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0f);
}