#version 450

layout(location = 0) in vec2 aPos; // Vertex position in NDC

uniform mat4 u_mvp;

void main()
{
    gl_Position = u_mvp * vec4(aPos, 0.0, 1.0);
}