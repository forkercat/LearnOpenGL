#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D scene;
uniform vec2 offsets[9];
uniform int edge_kernel[9];
uniform float blur_kernel[9];

uniform bool chaos;
uniform bool confuse;
uniform bool shake;

void main()
{
    FragColor = vec4(0.0f);
    vec3 samples[9];

    // sample from texture offsets if using convolution matrix
    if (chaos || shake)
    {
        for (int i = 0; i < 9; ++i)
        {
            samples[i] = vec3(texture(scene, TexCoords.st + offsets[i]));
        }
    }

    // process effects
    if (chaos)
    {
        for (int i = 0; i < 9; ++i)
        {
            FragColor += vec4(samples[i] * edge_kernel[i], 0.0f);
        }
        FragColor.a = 1.0f;
    }
    else if (confuse)
    {
        FragColor = vec4(1.0f - texture(scene, TexCoords).rgb, 1.0f);
    }
    else if (shake)
    {
        for (int i = 0; i < 9; ++i)
        {
            FragColor += vec4(samples[i] * blur_kernel[i], 0.0f);
        }
        FragColor.a = 1.0f;
    }
    else
    {
        FragColor = texture(scene, TexCoords);
    }
}