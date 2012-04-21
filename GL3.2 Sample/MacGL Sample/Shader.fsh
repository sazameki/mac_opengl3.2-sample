#version 150

in vec3 colorVarying;
in vec2 texUVVarying;

uniform sampler2D texture0;

out vec4 finalColor;

void main()
{
    vec4 texColor0 = texture(texture0, texUVVarying).rgba;

    vec3 color = texColor0.rgb;
    color *= colorVarying;

    finalColor = vec4(color, 1.0);
}
