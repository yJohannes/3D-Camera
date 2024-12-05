#version 450 core

layout(location = 0) in vec3 a_pos;
layout(location = 1) in vec3 a_normal;

// https://learnopengl.com/Lighting/Basic-Lighting

// uniform vec3 u_position;
uniform mat4 u_mvp;
uniform mat4 u_model;

out vec3 frag_position;
out vec3 frag_normal;

void main()
{
    // Normal is not transformed using MVP because it is redundant for the outcome
    // This is done to orient normals to model orientation
    // This is expensive to compute so it should just be done once on CPU
    frag_normal = mat3(transpose(inverse(u_model))) * a_normal;

    // Compute the position of the fragment in world space
    frag_position = vec3(u_model * vec4(a_pos, 1.0));
    
    // Transform the position to clip space
    gl_Position = u_mvp * vec4(a_pos, 1.0);
}