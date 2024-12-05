#version 450 core

// https://learnopengl.com/Lighting/Basic-Lighting

uniform vec3 u_frag_color;
uniform vec3 u_camera_position;
uniform bool u_apply_lighting;
uniform vec3 u_light_position;
uniform vec3 u_light_color;

in vec3 frag_position;
in vec3 frag_normal;

out vec4 frag_color;

float ambient_strength = 0.2;
vec3 ambient_light_color = vec3(1.0);

float specular_strength = 0.9;

vec3 diffuse(vec3 frag_normal)
{
    vec3 norm = normalize(frag_normal);
    vec3 light_dir = normalize(u_light_position - frag_position);

    float diff = max(dot(norm, light_dir), 0.0);
    return diff * u_light_color;
}

vec3 specular(vec3 camera_position)
{
    vec3 norm = normalize(frag_normal);
    vec3 view_dir = normalize(camera_position - frag_position);
    vec3 light_dir = normalize(u_light_position - frag_position);  

    vec3 reflection_dir = reflect(-light_dir, norm);

    float spec = pow(max(dot(view_dir, reflection_dir), 0.0), 64);
    return specular_strength * spec * u_light_color;
}

void main()
{
    vec3 result;
    if (u_apply_lighting)
    {
        vec3 ambient = ambient_strength * ambient_light_color;
        vec3 diffuse = diffuse(frag_normal);
        vec3 specular = specular(u_camera_position);

        result = (ambient + diffuse + specular) * u_frag_color;
    }
    else
    {
        result = u_frag_color;
    }

    frag_color = vec4(result, 1.0);
}