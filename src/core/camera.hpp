#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
private:
    glm::mat4 m_view;
    glm::mat4 m_projection;

    glm::vec3 m_position;
    glm::vec3 m_camera_target;
    glm::vec3 m_camera_direction;

    float m_fov;
    float m_aspect;
    float m_near;
    float m_far;

    float m_yaw;
    float m_pitch;

    glm::vec3 m_world_up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 m_front;
    glm::vec3 m_right;
    glm::vec3 m_up;
public:
    Camera(const glm::vec3 &position, float fov, float aspect, float near, float far)
        : m_position(position)
        , m_fov(fov)
        , m_aspect(aspect)
        , m_near(near)
        , m_far(far)
        , m_yaw(0.0f)
        , m_pitch(0.0f)
    {
        m_camera_target = glm::vec3(0.0f, 0.0f, 0.0f);
        update_view_matrix();
        update_projection_matrix();
    }

    void move(const glm::vec3 &delta)
    {
        m_camera_target = m_camera_target + delta;

        m_position += delta;
        update_view_matrix();
    }

    void look(const glm::vec2& delta)
    {
        float sensitivity = 0.1f;
        m_yaw += delta.x * sensitivity;
        m_pitch += delta.y * sensitivity;

        m_pitch = glm::clamp(m_pitch, -89.0f, 89.0f);

        // Calculate new direction vector using spherical coordinates
        glm::vec3 front;
        front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
        front.y = sin(glm::radians(m_pitch));
        front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
        
        m_front = glm::normalize(front);
        m_right = glm::normalize(glm::cross(m_front, m_world_up));
        m_up    = glm::normalize(glm::cross(m_right, m_front));

        update_view_matrix();
    }

    void zoom(float delta_fov)
    {
        m_fov += -delta_fov;
        m_fov = glm::clamp(m_fov, 30.0f, 120.0f);
        update_projection_matrix();
    }

    //////////// GETTERS ////////////
    //
    glm::mat4 get_view() const
    { return m_view; }

    glm::mat4 get_projection() const
    { return m_projection; }

    glm::mat4 get_mvp(const glm::mat4 &model) const
    { return m_projection * m_view * model; }

    glm::vec3 get_position()
    { return m_position; }

    float get_fov()
    { return m_fov; }

    //////////// SETTERS ////////////
    //
    void set_fov(float fov)
    {
        m_fov = fov;
        update_projection_matrix();
    }

    void set_position(const glm::vec3 &position)
    {
        if (position != m_position)
        {
            m_camera_target = m_camera_target - position;
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
        m_view = glm::lookAt(m_position, m_camera_target, m_up);
    }

    void update_projection_matrix()
    {
        m_projection = glm::perspective(glm::radians(m_fov), m_aspect, m_near, m_far);  
    }
};