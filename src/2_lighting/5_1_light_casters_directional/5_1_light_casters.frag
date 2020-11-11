#version 330 core
out vec4 FragColor;

struct Material
{
    sampler2D diffuse;  // used as ambient map as well
    sampler2D specular;
    float shininess;
};

struct Light
{
//    vec3 position;
    vec3 direction;  // no position anymore becasue it is a directional light

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 FragPos;  // interpolated via rasterization
in vec3 Normal;  // same
in vec2 TexCoords;  // same

uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main()
{
    // ambient
    vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;  // ambient_strength * object_color

    // diffuse
    vec3 norm = normalize(Normal);
//    vec3 lightDir = normalize(light.position - FragPos);
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;  // diffuse_strength * object_color

    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
    vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;  // specular_strength * object_color

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0f);
}
