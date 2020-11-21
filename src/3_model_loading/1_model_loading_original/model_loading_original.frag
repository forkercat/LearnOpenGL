#version 330 core
out vec4 FragColor;

in VS_OUT
{
    vec3 FragPos;
    vec2 TexCoords;
    vec3 TangentLightPos;
    vec3 TangentLightDir;
    vec3 TangentViewPos;
    vec3 TangentFragPos;
} fs_in;

struct Material
{
    sampler2D texture_diffuse1;
    sampler2D texture_specular1;
    sampler2D texture_normal1;
    float shininess;
};

struct Light
{
    vec3 position;
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

//uniform sampler2D texture_diffuse1;
uniform Material material;
uniform Light light;

void main()
{
    // obtain normal from normal map in range [0, 1]
    vec3 normall = texture(material.texture_normal1, fs_in.TexCoords).rgb;
    vec3 normal = normalize(normall * 2.0 - 1.0);

    // obtain diffuse and specular color
    vec3 baseColor = texture(material.texture_diffuse1, fs_in.TexCoords).rgb;
    vec3 specColor = texture(material.texture_specular1, fs_in.TexCoords).rrr;

    // ambient
    vec3 ambient = light.ambient * baseColor;

    // diffuse
//    vec3 lightDir = normalize(fs_in.TangentLightPos - fs_in.TangentFragPos);
    vec3 lightDir = light.direction;
    float diff = max(dot(normal, lightDir), 0.0f);
    vec3 diffuse = light.diffuse * diff * baseColor;

    // specular
    vec3 viewDir = normalize(fs_in.TangentViewPos - fs_in.TangentFragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0f), material.shininess);
    vec3 specular = light.specular * spec * specColor;

    vec3 result = ambient + diffuse + specular;
//    vec3 result = ambient + diffuse;
//    vec3 result = specular;
    FragColor = vec4(result, 1.0f);

    // debug normal
    // ------------
//    FragColor = vec4(normall, 1.0f);
}
