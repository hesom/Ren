R"(

#version 460

layout(location=0) in vec3 position;
layout(location=1) in vec3 normal;
layout(location=2) in vec2 uv;

out VertexData{
    smooth vec3 normal;
    smooth vec2 texCoord;
} vs_out;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 normalMatrix;

void main()
{
    vs_out.texCoord = uv;
    vs_out.normal = mat3(normalMatrix)*normal;
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0);
}

)"