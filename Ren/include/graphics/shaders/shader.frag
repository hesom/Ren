R"(
#version 460

in VertexData{
    smooth vec3 normal;
    smooth vec2 texCoord;
};
out vec4 fragColor;

uniform sampler2D diffuseTex;

void main()
{
    fragColor = texture(diffuseTex, texCoord);
}


)"