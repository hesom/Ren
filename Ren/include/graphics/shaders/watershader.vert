R"(
#version 460

#define MAX_LIGHTS 16

in vec2 position;

out vec4 clipSpace;
out vec2 texcoords;
out vec3 toCamera;
out vec3 fromLight[MAX_LIGHTS];

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

uniform vec3 lightPos[MAX_LIGHTS];
uniform vec3 cameraPos;

const float tiling = 6.0;

void main()
{
    vec4 worldPos = modelMatrix * vec4(position.x, 0.0, position.y, 1.0);
    toCamera = cameraPos - worldPos.xyz;
    for(int i = 0; i < MAX_LIGHTS; i++){
        fromLight[i] = worldPos.xyz - lightPos[i];
    }
    clipSpace = projectionMatrix * viewMatrix * worldPos;
    gl_Position = clipSpace;
    texcoords = vec2(position.x/2.0 + 0.5, position.y/2.0 + 0.5) * tiling;
}

)"