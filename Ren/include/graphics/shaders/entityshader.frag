R"(
#version 460

#define MAX_LIGHTS 16

in VertexData{
    smooth vec3 vnormal;
    smooth vec3 vtangent;
    smooth vec3 vlight[MAX_LIGHTS];
    smooth vec3 vview;
    smooth vec2 vtexcoord;
};
out vec4 fcolor;

uniform sampler2D diffuseMap;
uniform sampler2D normalMap;
uniform sampler2D specularMap;

uniform float hasNormalTex;
uniform float hasSpecularTex;

uniform vec3 lightColor[MAX_LIGHTS];
uniform vec3 cameraPos;

void main()
{   
    vec3 n = normalize(vnormal);

    vec3 t = normalize(vtangent);
    vec3 b = cross(n, t);
    mat3 T = mat3(t, b, n);
    vec3 normal = n;

    if(hasNormalTex > 0.5){
        n = texture(normalMap, vtexcoord).rgb;
        n = normalize(2.0*n - 1.0);
        normal = T*n;
    }

    const float kd = 0.5;
    vec3 ks = vec3(0.5);
    const float shininess = 120.0;

    if(hasSpecularTex > 0.5){
        ks = texture(specularMap, vtexcoord).rgb;
    }

    const float ka = 0.1;

    vec3 surface_color = texture(diffuseMap, vtexcoord).rgb;

    vec3 totalDiffuse = vec3(0.0);
    vec3 totalSpecular = vec3(0.0);
    vec3 totalAmbient = vec3(0.0);

    for(int i = 0; i < MAX_LIGHTS; i++){
        vec3 light = normalize(vlight[i]);
        vec3 view = normalize(vview);
        vec3 halfway = normalize(light + view);
        vec3 diffuse = surface_color * lightColor[i] * max(dot(light, normal), 0.0);
        vec3 specular = ks * lightColor[i] * pow(max(dot(halfway, normal), 0.0), shininess);
        vec3 ambient = ka*lightColor[i];

        totalDiffuse+=diffuse;
        totalSpecular+=specular;
        totalAmbient += ambient;
    }

    fcolor = vec4(surface_color * (totalDiffuse + totalSpecular + totalAmbient), 1.0);
}


)"