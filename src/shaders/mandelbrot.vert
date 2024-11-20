#version 450

uniform mat4 u_MVP;
layout(location = 0) in vec2 aPos; // Vertex position in NDC

out vec2 position;

void main()
{
    position = aPos;
    gl_Position = u_MVP * vec4(aPos, 0.0, 1.0);
    // gl_Position = vec4(aPos, 0.0, 1.0);
    gl_PointSize = 1.0;
}