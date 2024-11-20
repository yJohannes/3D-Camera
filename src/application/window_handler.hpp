#pragma once
#include <SFML/Graphics.hpp>
#include "event/event_manager.hpp"
#include "../common/vec.hpp"

class WindowHandler
{
private:
	sf::RenderWindow &r_window;
        EventManager m_event_manager;

	Vec2i m_prev_mouse_pos;
	bool  m_dragging = false;
        float m_zoom_strength = 1.1f;
public:
        Signal view_changed;

	float zoom = 1.f;
	Vec2i scroll_position;
	Vec2f offset;

	WindowHandler(sf::RenderWindow &target_window)
                : r_window(target_window)
                , m_event_manager()
                , view_changed()
	{
                init_events();
        }

	void process_events()
	{
		sf::Event event;
		while (r_window.pollEvent(event))
		{
                        m_event_manager.register_callback(event);
		}
		return;
	}
private:
    void init_events()
    {
        // Register events with member function pointers
        register_event_callback(sf::Event::Closed,               &WindowHandler::on_window_closed);
        register_event_callback(sf::Event::MouseButtonPressed,   &WindowHandler::on_mouse_pressed);
        register_event_callback(sf::Event::MouseButtonReleased,  &WindowHandler::on_mouse_released);
        register_event_callback(sf::Event::MouseWheelScrolled,   &WindowHandler::on_mouse_wheel_scrolled);
        register_event_callback(sf::Event::MouseMoved,           &WindowHandler::on_mouse_moved);
    }

    // Helper function to register event callbacks using member function pointers
    void register_event_callback(sf::Event::EventType type, void (WindowHandler::*handler)(const sf::Event&))
    {
        m_event_manager.add_callback(type, [this, handler](const sf::Event& event) {
            (this->*handler)(event);
        });
    }


    // Event handling functions
    void on_window_closed(const sf::Event& event)
    {
        r_window.close();
    }

    void on_mouse_pressed(const sf::Event& event)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            m_dragging = true;
            m_prev_mouse_pos = sf::Mouse::getPosition(r_window);
        }
    }

    void on_mouse_released(const sf::Event& event)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            m_dragging = false;
        }
    }

    void on_mouse_wheel_scrolled(const sf::Event& event)
    {
        scroll_position = sf::Mouse::getPosition(r_window);

        float delta = event.mouseWheelScroll.delta;
        zoom *= (delta > 0) ? m_zoom_strength : 1.f / m_zoom_strength;

        view_changed.emit();
    }

    void on_mouse_moved(const sf::Event& event)
    {
        if (m_dragging)
        {
            Vec2i mouse_position = sf::Mouse::getPosition(r_window);
            offset += vec_cast<float>(m_prev_mouse_pos - mouse_position) * (1.0f / zoom);
            m_prev_mouse_pos = mouse_position;

            view_changed.emit();
        }
    }


/*
        void init_events()
        {

                m_event_manager.add_callback(sf::Event::Closed, [this](const sf::Event &event) {
                        r_window.close();
                });
                
                m_event_manager.add_callback(sf::Event::MouseButtonPressed, [this](const sf::Event &event) {
                        if (event.mouseButton.button == sf::Mouse::Left)
                        {
                                m_dragging = true;
                                m_prev_mouse_pos = sf::Mouse::getPosition(r_window);
                        }

                        // more ...
                });

                m_event_manager.add_callback(sf::Event::MouseButtonReleased, [this](const sf::Event &event) {
                        if (event.mouseButton.button == sf::Mouse::Left)
                        {
                                m_dragging = false;
                        }
                });

                m_event_manager.add_callback(sf::Event::MouseWheelScrolled, [this](const sf::Event &event) {
                        scroll_position = sf::Mouse::getPosition(r_window);

                        float ds = event.mouseWheelScroll.delta;
                        if (ds > 0)      zoom *= m_zoom_strength; 
                        else if (ds < 0) zoom /= m_zoom_strength;

                        view_changed.emit();
                });

                m_event_manager.add_callback(sf::Event::MouseMoved, [this](const sf::Event &event) {
                        if (m_dragging)
                        {
                                Vec2i mouse_position = sf::Mouse::getPosition(r_window);
                                offset += vec_cast<float>(m_prev_mouse_pos - mouse_position) * (1.0f / zoom);
                                m_prev_mouse_pos = mouse_position;

                                view_changed.emit();
                        }
                });
        }

*/
};
