#pragma once

#include <glad/glad.h>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>

#include "window_handler.hpp"
#include "../core/mandelbrot.hpp"

class MainWindow
{
private:
    sf::RenderWindow m_window;  // sf::Window for pure OpenGL rendering
    WindowHandler    m_handler;

    Mandelbrot m_mandelbrot;

    const uint32_t m_width;
    const uint32_t m_height;

    sf::Transform m_transform;
public:
    MainWindow(uint32_t width, uint32_t height, const std::string &title, sf::ContextSettings context, uint32_t style = sf::Style::Default)
        : m_window(sf::VideoMode(width, height), title, style, context)
        , m_handler(m_window)
        , m_mandelbrot()
        , m_width(width)
        , m_height(height)
    {
        m_window.setActive(true);
        m_window.setFramerateLimit(60);
        m_window.setVerticalSyncEnabled(false);
        init_signals();
    }

    void run()
    {
        while (m_window.isOpen())
        {
            m_handler.process_events();
    
            glClear(GL_COLOR_BUFFER_BIT);
            m_mandelbrot.render();
            m_window.display();
        }
    }

void update_projection()
{
    // sf::Vector2i mousePosition = sf::Mouse::getPosition(m_window); // window is your sf::RenderWindow

    // float ndcX = 2.0f * mousePosition.x / m_window.getSize().x - 1.0f;
    // float ndcY = 1.0f - 2.0f * mousePosition.y / m_window.getSize().y;

    // glMatrixMode(GL_PROJECTION);
    // glLoadIdentity();

    // static Vec2f center = {static_cast<float>(m_width / 2), static_cast<float>(m_height / 2)};
    // const Vec2f offset = vec_cast<float>(m_handler.offset) / static_cast<float>(m_width); // normalize 
    // const Vec2f zoom = {m_handler.zoom, m_handler.zoom};

    // // Apply translation to the center, scale, then translate by offset
    // glTranslatef(center.x, center.y, 0.0f);      // Move to center
    // glScalef(zoom.x, zoom.y, 1.0f);              // Apply zoom
    // glTranslatef(-center.x - offset.x, -center.y + offset.y, 0.0f); // Pan with offset

}

private:
    void init_signals()
    {
        m_handler.view_changed.connect(std::bind(&MainWindow::update_projection, this));
    }
};