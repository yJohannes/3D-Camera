#pragma once

#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Cube
{
private:
    std::vector<float> m_vertices;
    glm::mat4 m_model;

    glm::vec3 m_position;
    glm::vec3 m_axis;
    float m_angle;

    GLuint VAO, VBO;
public:
    Cube() : m_position(0.0f), m_vertices(), VAO(0), VBO(0) {}

    Cube(const glm::vec3 &position, const std::vector<float> &vertices)
        : m_position(position)
        , m_vertices(vertices)
    {
        m_model = glm::translate(glm::mat4(1.0f), position);
    }

    ~Cube()
    {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }

    void init()
    {
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(float), &m_vertices[0], GL_STATIC_DRAW);

        // Position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // Normal attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void bind() const
    {
        glBindVertexArray(VAO);
    }

    void unbind() const
    {
        glBindVertexArray(0);
    }

    void draw() const
    {
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    void move(const glm::vec3& delta)
    {
        m_model = glm::translate(m_model, delta);
    }

    void rotate(float delta, const glm::vec3& axis)
    {
        m_model = glm::rotate(m_model, delta, axis);
    }

    void set_position(const glm::vec3& position)
    {
        m_position = position;
        m_model = glm::mat4(1.0f);
        m_model = glm::translate(m_model, m_position);
        m_model = glm::rotate(m_model, m_angle, m_axis);
    }

    void set_rotation(float angle, const glm::vec3& axis)
    {
        m_angle = angle;
        m_axis = axis;
        m_model = glm::mat4(1.0f);
        m_model = glm::translate(m_model, m_position);
        m_model = glm::rotate(m_model, m_angle, m_axis);
    }

    inline glm::mat4 model() { return m_model; }
    inline glm::vec3 position() { return m_position; }
};