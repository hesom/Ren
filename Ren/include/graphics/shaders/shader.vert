R"(

#version 400

layout(location=0) in vec3 position;
layout(location=1) in vec3 normal;
layout(location=2) in vec2 uv;

out vec3 color;

void main()
{
    color = position;
    gl_Position = vec4(position, 1.0);
}

)"