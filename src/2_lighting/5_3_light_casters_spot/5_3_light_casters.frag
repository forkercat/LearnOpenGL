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

in vec3 FragPos;  // interpolated via rasterization
in vec3 Normal;  // same
in vec2 TexCoords;  // same

uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main()
{
    vec3 lightDir = normalize(light.position - FragPos);

    // check if lighting is inside the spotlight cone
    float theta = dot(lightDir, normalize(-light.direction));

    if (theta > light.cutOff)  // cosine comparison
    {
        // ambient
        vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;  // ambient_strength * object_color

        // diffuse
        vec3 norm = normalize(Normal);
        float diff = max(dot(norm, lightDir), 0.0f);
        vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;  // diffuse_strength * object_color

        // specular
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
        vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;  // specular_strength * object_color

        // attenuation
        float distance = length(light.position - FragPos);
        float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

        // remove attenuation from ambient, as otherwise at large distances the light would be darker inside than outside the spotlight due the ambient term in the else branche
        // ambient *= attenuation;
        diffuse *= attenuation;
        specular *= attenuation;

        vec3 result = ambient + diffuse + specular;
        FragColor = vec4(result, 1.0f);
    }
    else
    {
        FragColor = vec4(light.ambient * texture(material.diffuse, TexCoords).rgb, 1.0f);
    }
}
