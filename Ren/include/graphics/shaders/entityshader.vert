R"(

#version 460

#define MAX_LIGHTS 16

layout(location=0) in vec3 position;
layout(location=1) in vec3 normal;
layout(location=2) in vec2 texcoord;
layout(location=3) in vec3 tangent;

out VertexData{
    smooth vec3 vnormal;
    smooth vec3 vtangent;
    smooth vec3 vlight[MAX_LIGHTS];
    smooth vec3 vview;
    smooth vec2 vtexcoord;
};

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 normalMatrix;

uniform vec3 cameraPos;
uniform vec3 lightPos[MAX_LIGHTS];

uniform vec4 plane;

void main()
{
    
    vec4 worldPos = modelMatrix * vec4(position, 1.0);

    vec3 pos = (viewMatrix * modelMatrix * vec4(position, 1.0)).xyz;

    gl_ClipDistance[0] = dot(worldPos, plane);

    vec3 eye_pos = vec3(0.0);
    vnormal = mat3(normalMatrix)*normal;
    vtangent = mat3(viewMatrix * modelMatrix)*tangent;

    for(int i = 0; i < MAX_LIGHTS; i++){
        vec3 light_pos = (viewMatrix * vec4(lightPos[i], 1.0)).xyz;
        vlight[i] = light_pos - pos;
    }
    vview = eye_pos - pos;
    vtexcoord = texcoord;
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0);
}

)"