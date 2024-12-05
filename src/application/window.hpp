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
    const uint32_t m_frame_limit = 165;

    sf::Clock m_clock;
    sf::Window m_window;  // sf::Window for pure OpenGL rendering
    WindowHandler m_handler;

    Scene* m_scene;

public:
    MainWindow(uint32_t width, uint32_t height, const std::string &title, sf::ContextSettings context, uint32_t style = sf::Style::Default)
        : m_width(width)
        , m_height(height)
        , m_window(sf::VideoMode(width, height), title, style, context)
        , m_handler(m_window)
        , m_scene(nullptr)
    {
        // Load OpenGL
        m_window.setActive(true);
        if (!gladLoadGL())
        {
            std::cerr << "Failed to initialize GLAD\n";
        }
    
        glClearColor(0.14f, 0.14f, 0.14f, 1.0f);
        glViewport(0, 0, width, height);
        glEnable(GL_DEPTH_TEST);

        // Window settings
        m_window.setFramerateLimit(m_frame_limit);
        m_window.setVerticalSyncEnabled(true);
        m_window.setMouseCursorVisible(false);
        m_window.setMouseCursorGrabbed(true);

        // Initialize objects
        m_scene = new Scene(static_cast<float>(width) / static_cast<float>(height));

        // Initialize signals
        init_signals();
    }

    ~MainWindow()
    {
        if (m_scene)
        {
            delete m_scene;
        }
    }

    void run()
    {
        while (m_window.isOpen())
        {
            m_handler.process_events();

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            m_scene->render(m_clock.getElapsedTime().asSeconds());
            m_window.display();
        }
    }

private:
    void init_signals()
    {
        m_handler.window_resized.connect([](const Vec2u& size) {glViewport(0, 0, size.x, size.y);});
        m_handler.mouse_scrolled.connect(m_scene->camera(), &Camera::zoom);
        m_handler.position_changed.connect(m_scene->camera(), &Camera::move);
        m_handler.mouse_moved.connect(m_scene->camera(), &Camera::look);
    }
};