#pragma once
#include "camera.hpp"
#include "shader.hpp"
#include "cube.hpp"

class Scene
{
private:
    Camera m_camera;
    RenderShader m_render_shader;

    Cube m_cube;
    Cube m_light;
public:
    Scene(float aspect_ratio)
        : m_camera(glm::vec3(0.0f, 0.0f, 0.0f), 45.0f, aspect_ratio, 0.1f, 100.0f)
        , m_render_shader("src/shaders/cube.vert", "src/shaders/cube.frag")
    {
        std::vector<float> vertices = {
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
             0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
             0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
             0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 

            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
             0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

             0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
             0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
             0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
             0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
             0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
             0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
             0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
             0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
             0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
        };

        m_cube = Cube(glm::vec3(0.0f, 0.0f, 0.0f), vertices);
        m_cube.init();

        m_light = Cube(glm::vec3(10.0f, 5.0f, 5.0f), vertices);
        m_light.init();
    }

    Camera* camera()
    {
        return &m_camera;
    }

    void render(float time)
    {
        m_render_shader.bind();
        m_render_shader.set_vec3("u_camera_position", m_camera.get_position());

        float radius = 4.5f;
        float speed = 1.0f;

        float x = radius * cos(speed * time);
        float z = radius * sin(speed * time);
        float y = 2.0f;

        glm::vec3 light_pos = {x, y, z};
        m_render_shader.set_vec3("u_light_position", light_pos);
        m_render_shader.set_vec3("u_light_color", glm::vec3(1.0f, 1.0f, 1.0f));

        m_cube.set_rotation(time * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
        m_render_shader.set_mat4("u_mvp", m_camera.get_mvp(m_cube.model()));
        m_render_shader.set_mat4("u_model", m_cube.model());
        m_render_shader.set_vec3("u_frag_color", glm::vec3(1.0f, 0.5f, 0.25f));

        m_render_shader.set_bool("u_apply_lighting", true);
        m_cube.bind();  
        m_cube.draw();
        m_cube.unbind();
        m_render_shader.set_bool("u_apply_lighting", false);

        m_light.set_position(light_pos);
        m_light.set_rotation(-speed * time, glm::vec3(0.0f, 1.0f, 0.0f));
        m_render_shader.set_mat4("u_mvp", m_camera.get_mvp(m_light.model()));
        m_render_shader.set_mat4("u_model", m_light.model());
        m_render_shader.set_vec3("u_frag_color", glm::vec3(1.0f, 1.0f, 1.0f));

        m_light.bind();
        m_light.draw();
        m_light.unbind();

        m_render_shader.unbind();
    }
};