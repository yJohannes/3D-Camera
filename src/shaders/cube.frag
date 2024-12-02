#version 450 core

in vec3 camera_position;
in vec4 frag_position;
out vec4 frag_color;

void main()
{
    float camera_dist = length(camera_position - frag_position.xyz);
    frag_color = vec4(0.0,1.0 - camera_dist,1.0,1.0);
}