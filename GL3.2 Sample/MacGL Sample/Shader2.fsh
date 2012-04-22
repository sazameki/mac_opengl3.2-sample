#version 150

in vec2 texUVVarying;

uniform sampler2D texture0;
uniform float time;

out vec4 finalColor;

vec4 convertToSepia(vec4 color)
{
    const vec3 rgb_to_yuv = vec3(0.299, 0.587, 0.114);
    const vec3 i_to_rgb = vec3(0.956, -0.272, -1.108);
    const vec3 q_to_rgb = vec3(0.620, -0.647, 1.705);
    const float i = 0.2;
    const float q = 0.0;
    
    float y = dot(rgb_to_yuv, color.rgb);
    y *= 1.4;
    if (y > 1.0) {
        y = 1.0;
    }
    return vec4(y+i_to_rgb*i+q_to_rgb*q, color.a);
}

vec4 addScanLine(vec4 color)
{
    const float density = 480.0*3.14/2.0;
    //const float brightness = 0.75;
    const float brightness = 0.5;
    
    vec4 ret = color;
    ret.rgb *= (sin(texUVVarying.y*density-time)+1.0)*0.5*(1.0-brightness)+brightness;
    return ret;
}

void main()
{
    vec4 texColor0 = texture(texture0, texUVVarying).rgba;
    
    vec4 color = texColor0;
    color = convertToSepia(color);
    color = addScanLine(color);

    finalColor = color;
}
