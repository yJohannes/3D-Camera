#pragma once

#include <vector>

#include <glm/glm.hpp>
#include <glad/glad.h>

class Cube
{
private:
    glm::vec3 m_position;
    std::vector<float> m_vertices;
    std::vector<unsigned int> m_indices;
    GLuint VAO, VBO, EBO;
public:
    Cube() : m_position(0.0f), m_vertices(), m_indices(), VAO(0), VBO(0), EBO(0)
    {
    }

    Cube(const glm::vec3 &position, const std::vector<float> &vertices, const std::vector<unsigned int> &indices)
        : m_position(position)
        , m_vertices(vertices)
        , m_indices(indices)
    {
    }

    ~Cube()
    {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }

    void init()
    {
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(float), &m_vertices[0], GL_STATIC_DRAW);

        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), &m_indices[0], GL_STATIC_DRAW);

        // Position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }


    void bind() const
    {
        glBindVertexArray(VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    }

    void unbind() const
    {
        glBindVertexArray(0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
};