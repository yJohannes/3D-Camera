#pragma once

#include <vector>
#include <glm/glm.hpp>

struct Cube
{
    glm::vec3 position;
    std::vector<float> vertices;

    Cube() : position(0.0f), vertices() {}
};