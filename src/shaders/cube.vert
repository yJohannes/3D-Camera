#version 450 core

layout(location = 0) in vec3 a_pos;

uniform mat4 u_mvp;
uniform vec3 u_camera_position;

out vec3 camera_position;
out vec4 frag_position;

void main()
{
    camera_position = u_camera_position;
    frag_position = u_mvp * vec4(a_pos, 1.0);
    gl_Position = frag_position;
}