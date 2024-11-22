#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
private:
    glm::mat4 m_view;
    glm::mat4 m_projection;

    glm::vec3 m_position;
    glm::vec3 m_camera_target = glm::vec3(0.0f);
    glm::vec3 m_camera_direction;

    float m_fov;
    float m_aspect;
    float m_near;
    float m_far;
public:
    Camera(const glm::vec3 &position, float fov, float aspect, float near, float far)
        : m_fov(fov)
        , m_aspect(aspect)
        , m_near(near)
        , m_far(far)
    {
        // glm::vec3 right = glm::normalize(glm::cross(up, m_camera_direction));
        // glm::vec3 camera_up = glm::cross(m_camera_direction, right);
        update_view_matrix();
        update_projection_matrix();
    }

    glm::mat4 get_view() const
    { return m_view; }
    glm::mat4 get_projection() const
    { return m_projection; }
    glm::mat4 get_mvp(const glm::mat4 &model) const
    { return m_projection * m_view * model; }

    void move(const glm::vec3 &delta)
    {
        m_position += delta;
        update_view_matrix();
    }

    void zoom(float delta_fov)
    {
        m_fov += delta_fov;
        m_fov = glm::clamp(m_fov, 30.0f, 120.0f);
        update_projection_matrix();
    }

    void set_position(const glm::vec3 &position)
    {
        if (position != m_position)
        {
            m_position = position;
            update_view_matrix();
        }
    }

    void set_target(const glm::vec3 &target)
    {
        m_camera_target = target;
        update_view_matrix();
    }

    void set_aspect_ratio(float aspect)
    {
        m_aspect = aspect;
        update_projection_matrix();
    }

private:
    void update_view_matrix()
    {
        // actually pointing in the reverse direction
        m_camera_direction = glm::normalize(m_position - m_camera_target);
        m_view = glm::lookAt(m_position, m_camera_target, glm::vec3(0.0f, 1.0f, 0.0f));
    }

    void update_projection_matrix()
    {
        m_projection = glm::perspective(glm::radians(m_fov), m_aspect, m_near, m_far);  
    }

};