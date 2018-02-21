R"(
#version 460

#define MAX_LIGHTS 16

in vec4 clipSpace;
in vec2 texcoords;
in vec3 toCamera;
in vec3 fromLight[MAX_LIGHTS];

out vec4 fcolor;

uniform sampler2D reflectionTexture;
uniform sampler2D refractionTexture;
uniform sampler2D dudvMap;
uniform sampler2D normalMap;

uniform vec3 lightColor[MAX_LIGHTS];
const float attenuationConstant = 1.0;
uniform float attenuationLinear[MAX_LIGHTS];
uniform float attenuationQuadratic[MAX_LIGHTS];
uniform float animationTimer;

const float waveStrength = 0.01;
const float reflectivity = 0.1;

void main()
{
    vec2 ndc = (clipSpace.xy/clipSpace.w)/2.0 + 0.5;
    vec2 refractTexcoords = ndc;
    vec2 reflectTexcoords = vec2(ndc.x, -ndc.y);
    vec3 viewVector = normalize(toCamera);
    float fresnelFactor = dot(viewVector, vec3(0.0, 1.0, 0.0));

    vec2 distortedTexcoords = texture(dudvMap, vec2(texcoords.x + animationTimer, texcoords.y)).rg*0.1;
    distortedTexcoords = texcoords + vec2(distortedTexcoords.x, distortedTexcoords.y + animationTimer);
    vec2 totalDistortion = (texture(dudvMap, distortedTexcoords).rg * 2.0 - 1.0) * waveStrength;

    refractTexcoords += totalDistortion;
    refractTexcoords = clamp(refractTexcoords , 0.001, 0.999);

    reflectTexcoords += totalDistortion;
    reflectTexcoords.x = clamp(reflectTexcoords.x, 0.001, 0.999);
    reflectTexcoords.y = clamp(reflectTexcoords.y, -0.999, -0.001);
    

    vec4 reflectColor = texture(reflectionTexture, reflectTexcoords);
    vec4 refractColor = texture(refractionTexture, refractTexcoords);

    vec4 normalMapColor = texture(normalMap, distortedTexcoords);
    vec3 normal = normalize(vec3(normalMapColor.r * 2.0 -1.0, normalMapColor.b, normalMapColor.g * 2.0 -1.0));

    vec3 totalSpecular = vec3(0.0);

    for(int i = 0; i < MAX_LIGHTS; i++){
        float dist = length(fromLight[i]);
        float attenuation = 1.0 / (attenuationConstant + dist*(attenuationLinear[i] + dist*(attenuationQuadratic[i])));
        vec3 reflectedLight = reflect(normalize(fromLight[i]), normal);
        float specular = pow(max(dot(reflectedLight, viewVector), 0.0), 120.0);
        totalSpecular += attenuation*(specular * reflectivity * lightColor[i]);
    }

    fcolor = mix(reflectColor, refractColor, fresnelFactor);
    fcolor = mix(fcolor, vec4(0.0, 0.2, 0.7, 1.0), 0.1);
    fcolor += vec4(totalSpecular, 0.0);
}

)"