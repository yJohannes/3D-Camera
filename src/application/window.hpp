#pragma once

#include <glad/glad.h>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>

#include "window_handler.hpp"
#include "../core/scene.hpp"

class MainWindow
{
private:
    const uint32_t m_width;
    const uint32_t m_height;

    sf::RenderWindow m_window;  // sf::Window for pure OpenGL rendering
    sf::Clock m_clock;
    WindowHandler m_handler;

    Scene m_scene;

public:
    MainWindow(uint32_t width, uint32_t height, const std::string &title, sf::ContextSettings context, uint32_t style = sf::Style::Default)
        : m_width(width)
        , m_height(height)
        , m_window(sf::VideoMode(width, height), title, style, context)
        , m_handler(m_window)
        , m_scene(static_cast<float>(width) / static_cast<float>(height))
    {
        m_window.setActive(true);
        m_window.setFramerateLimit(60);
        m_window.setVerticalSyncEnabled(true);

        glViewport(0, 0, width, height);

        init_signals();
    }

    void run()
    {
        while (m_window.isOpen())
        {
            m_handler.process_events();
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            m_scene.render(m_clock.getElapsedTime().asSeconds());
            m_window.display();
        }
    }

private:
    void init_signals()
    {
        m_handler.window_resized.connect([](const Vec2u& size) {glViewport(0, 0, size.x, size.y);});

        m_handler.mouse_scrolled.connect(m_scene.camera(), &Camera::zoom);
        m_handler.position_changed.connect(m_scene.camera(), &Camera::move);
        m_handler.mouse_moved.connect(m_scene.camera(), &Camera::look);
    }
};