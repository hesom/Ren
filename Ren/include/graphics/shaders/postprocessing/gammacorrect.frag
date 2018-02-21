R"(
#version 460

uniform sampler2D image;

in vec2 uv;
out vec4 fcolor;

const float gamma = 2.2;

void main(void)
{
    fcolor = texture(image, uv);
    fcolor.rgb = pow(fcolor.rgb, vec3(1.0/gamma));
}
)"