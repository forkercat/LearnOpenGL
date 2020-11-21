#version 330 core
out vec4 FragColor;

in VS_OUT
{
    vec3 FragPos;
    vec2 TexCoords;
    vec3 TangentLightPos;
    vec3 TangentViewPos;
    vec3 TangentFragPos;
} fs_in;

uniform sampler2D diffuseMap;
uniform sampler2D normalMap;
uniform sampler2D depthMap;

uniform float height_scale;

vec2 ParallaxMapping(vec2 texCoords, vec3 viewDir);

void main()
{
    vec3 viewDir = normalize(fs_in.TangentViewPos - fs_in.TangentFragPos);
    vec2 newTexCoords = ParallaxMapping(fs_in.TexCoords, viewDir);

    // obtain normal from normal map in range [0, 1]
    vec3 normal = texture(normalMap, newTexCoords).rgb;
    normal = normalize(normal * 2.0f - 1.0f);  // in tangent space

    // get diffuse color
    vec3 color = texture(diffuseMap, newTexCoords).rgb;

    // ambient
    vec3 ambient = 0.1f * color;

    // diffuse
    vec3 lightDir = normalize(fs_in.TangentLightPos - fs_in.TangentFragPos);
    float diff = max(dot(lightDir, normal), 0.0f);
    vec3 diffuse = diff * color;

    // specular
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0f), 32.0f);
    vec3 specular = vec3(0.2f) * spec;

    FragColor = vec4(ambient + diffuse + specular, 1.0f);
}

vec2 ParallaxMapping(vec2 texCoords, vec3 viewDir)
{
    float height = texture(depthMap, texCoords).r;
    // .z > 0
//    vec2 p = -viewDir.xy * (height * height_scale);
    vec2 p = -viewDir.xy / viewDir.z * (height * height_scale);
    return texCoords + p;
}