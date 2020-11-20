#version 330 core
out vec4 FragColor;

in VS_OUT
{
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLightSpace;
} fs_in;

uniform sampler2D diffuseTexture;
uniform sampler2D shadowMap;

uniform vec3 lightPos;
uniform vec3 viewPos;

float ShadowCalculation(vec4 fragPosLightSpace, vec3 normal, vec3 lightDir)
{
    // perform perspective division
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform from [-1, 1] to [0, 1] range
    projCoords = projCoords * 0.5f + 0.5f;

    if (projCoords.z > 1.0f)
    {
        return 0.0f;  // far away from far plane -> no shadow
    }

    // closest depth
    float closestDepth = texture(shadowMap, projCoords.xy).r;
    // current depth
    float currentDepth = projCoords.z;

    float shadow;
    // float bias = 0.05f;
    float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);
//    shadow = (currentDepth - bias > closestDepth) ? 1.0f : 0.0f;

    // PCF (percentage-closer filtering)
    vec2 texelSize = 1.0f / textureSize(shadowMap, 0);
    for (int x = -2; x <= 2; ++x)
    {
        for (int y = -2; y <= 2; ++y)
        {
            vec2 offset = texelSize * vec2(x, y);
            float pcfDepth = texture(shadowMap, projCoords.xy + offset).r;
            shadow += currentDepth - bias > pcfDepth ? 1.0f : 0.0f;
        }
    }
    shadow /= 25.0f;

    return shadow;
}

void main()
{
    vec3 color = texture(diffuseTexture, fs_in.TexCoords).rgb;
    vec3 normal = normalize(fs_in.Normal);
    vec3 lightColor = vec3(0.3f);

    // ambient
    vec3 ambient = 0.3f * color;

    // diffuse
    vec3 lightDir = normalize(lightPos - fs_in.FragPos);
    float diff = max(dot(lightDir, normal), 0.0f);
    vec3 diffuse = diff * lightColor;

    // specular
    vec3 viewDir = normalize(viewPos - fs_in.FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = 0.0f;
    vec3 halfwayDir = normalize(lightDir + viewDir);
    spec = pow(max(dot(normal, halfwayDir), 0.0f), 64.0f);
    vec3 specular = spec * lightColor;

    // calculate shadow
    float shadow = ShadowCalculation(fs_in.FragPosLightSpace, normal, lightDir);
    vec3 lighting = (ambient + (1.0f - shadow) * (diffuse + specular)) * color;

    FragColor = vec4(lighting, 1.0f);
}