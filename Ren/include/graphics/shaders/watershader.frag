R"(
#version 460

in vec4 clipSpace;

out vec4 fcolor;

uniform sampler2D reflectionTexture;
uniform sampler2D refractionTexture;

void main()
{
    vec2 ndc = (clipSpace.xy/clipSpace.w)/2.0 + 0.5;
    vec2 refractTexcoords = ndc;
    vec2 reflectTexcoords = vec2(ndc.x, -ndc.y);
    vec4 reflectColor = texture(reflectionTexture, reflectTexcoords);
    vec4 refractColor = texture(refractionTexture, refractTexcoords);

    fcolor = mix(reflectColor, refractColor, 0.5);
}

)"