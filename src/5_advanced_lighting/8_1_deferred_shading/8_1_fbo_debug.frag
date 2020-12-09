#version 330
out vec4 FragColor;
in vec2 TexCoords;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedoSpec;

void main()
{
    vec2 screenSize = textureSize(gPosition, 0);
    float screenWidth = screenSize.x * 2;  // retina
    float screenHeight = screenSize.y * 2;

    // border
    const float borderWidth = 6;
    const vec4 borderColor = vec4(0.9f, 0.9f, 0.9f, 1.0f);
    if (gl_FragCoord.x >= screenWidth / 2 - borderWidth && gl_FragCoord.x <= screenWidth / 2 + borderWidth)
    {
        FragColor = borderColor;
        return;
    }
    if (gl_FragCoord.y >= screenHeight / 2 - borderWidth && gl_FragCoord.y <= screenHeight / 2 + borderWidth)
    {
        FragColor = borderColor;
        return;
    }

    if (gl_FragCoord.x < screenWidth / 2.0f)
    {
        if (gl_FragCoord.y > screenHeight / 2.0f)
        {
            // gPosition
            vec2 texCoords = TexCoords * 2;
            FragColor = texture(gPosition, texCoords);
        }
        else
        {
            // gAlbedo
            vec2 texCoords = vec2((TexCoords.x - 0.5f) * 2, TexCoords.y * 2);
            FragColor = vec4(texture(gAlbedoSpec, texCoords).rgb, 1.0f);
        }
    }
    else
    {
        if (gl_FragCoord.y > screenHeight / 2.0f)
        {
            // gNormal
            vec2 texCoords = vec2((TexCoords.x - 0.5f) * 2, TexCoords.y * 2);
            FragColor = vec4(texture(gNormal, texCoords).rgb, 1.0f);
        }
        else
        {
            // gSpec
            vec2 texCoords = vec2((TexCoords.x - 0.5f) * 2, (TexCoords.y - 0.5f) * 2);
            FragColor = vec4(texture(gAlbedoSpec, texCoords).rrr, 1.0f);
        }
    }
}
