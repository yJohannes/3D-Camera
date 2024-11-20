#pragma once

#include <iostream>

#include <glad/glad.h>
#include <SFML/OpenGL.hpp>

class Renderer
{
public:
    Renderer()
    {
        if (!gladLoadGL())
            {
                std::cerr << "Failed to initialize GLAD\n";
            }
    }

    ~Renderer()
    {
    }

};