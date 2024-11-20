#pragma once

#include <glad/glad.h>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>

#include "window_handler.hpp"

class MainWindow
{
private:
    sf::RenderWindow m_window;  // sf::Window for pure OpenGL rendering
    WindowHandler    m_handler;

    const uint32_t m_width;
    const uint32_t m_height;

    sf::Transform m_transform;
public:
    MainWindow(uint32_t width, uint32_t height, const std::string &title, sf::ContextSettings context, uint32_t style = sf::Style::Default)
        : m_window(sf::VideoMode(width, height), title, style, context)
        , m_handler(m_window)
        , m_width(width)
        , m_height(height)
    {
        m_window.setActive(true);
        m_window.setFramerateLimit(60);
        m_window.setVerticalSyncEnabled(true);
        init_signals();
    }

    void run()
    {
        while (m_window.isOpen())
        {
            m_handler.process_events();
            // glClear(GL_COLOR_BUFFER_BIT);
            m_window.display();
        }
    }

private:
    void init_signals()
    {
        // m_handler.view_changed.connect(std::bind(&MainWindow::update_projection, this));
    }
};