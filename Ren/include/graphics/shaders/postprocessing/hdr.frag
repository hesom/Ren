R"(
#version 460

uniform sampler2D image;

in vec2 uv;
out vec4 fcolor;

const float exposure = 1.0;

void main(void)
{
    vec3 hdrColor = texture(image, uv).rgb;

    //vec3 mapped = hdrColor / (hdrColor + vec3(1.0));
    vec3 mapped = vec3(1.0) - exp(-hdrColor * exposure);

    fcolor = vec4(mapped, 1.0);
}
)"