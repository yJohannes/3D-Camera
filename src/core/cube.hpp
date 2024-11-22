#pragma once

#include <vector>

#include <glm/glm.hpp>
#include <glad/glad.h>

struct Cube
{
    glm::vec3 position;
    std::vector<float> vertices;
    GLuint VAO, VBO, EBO;

    Cube() : position(0.0f), vertices()
    {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        bind();
        
    }

    void bind()
    {
        glBindVertexArray(VAO);
    }
};