#pragma once
#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>
#include "event/event_manager.hpp"
#include "../common/vec.hpp"

class WindowHandler
{
private:
	sf::RenderWindow &r_window;
    EventManager m_event_manager;

	Vec2i m_prev_mouse_pos;
	bool  m_dragging = false;
public:
    // Emit amount
    Signal<const Vec2u&> window_resized;

    // Emit delta
    Signal<float> mouse_scrolled;
    Signal<const glm::vec2&> mouse_moved;
    Signal<const glm::vec3&> position_changed;
public:
	WindowHandler(sf::RenderWindow &target_window)
        : r_window(target_window)
        , m_event_manager()
	{
        init_events();
    }

	void process_events()
	{
		sf::Event event;
		while (r_window.pollEvent(event))
		{
            m_event_manager.trigger_event_callbacks(event);
		}
		return;
	}
private:
    void init_events()
    {
        m_event_manager.add_callback(sf::Event::Closed,              this, &WindowHandler::on_window_closed);
        m_event_manager.add_callback(sf::Event::Resized,             this, &WindowHandler::on_window_resize);

        m_event_manager.add_callback(sf::Event::MouseButtonPressed,  this, &WindowHandler::on_mouse_pressed);
        m_event_manager.add_callback(sf::Event::MouseButtonReleased, this, &WindowHandler::on_mouse_released);
        m_event_manager.add_callback(sf::Event::MouseWheelScrolled,  this, &WindowHandler::on_mouse_wheel_scrolled);
        m_event_manager.add_callback(sf::Event::MouseMoved,          this, &WindowHandler::on_mouse_moved);

        m_event_manager.add_callback(sf::Event::KeyPressed,          this, &WindowHandler::on_key_pressed);
    }

    void on_window_closed(const sf::Event& event)
    {
        r_window.close();
    }

    void on_window_resize(const sf::Event& event)
    {
        window_resized.emit(r_window.getSize());
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
        float delta = event.mouseWheelScroll.delta;
        mouse_scrolled.emit(delta);
    }

    void on_mouse_moved(const sf::Event& event)
    {
        Vec2i mpos = sf::Mouse::getPosition(r_window);
        Vec2f delta = vec_cast<float>(m_prev_mouse_pos - mpos);
        m_prev_mouse_pos = mpos;

        mouse_moved.emit({delta.x, delta.y});
    }
    
    void on_key_pressed(const sf::Event& event)
    {
        glm::vec3 delta(0.0f);

        switch (event.key.code)
        {
        case sf::Keyboard::W:
            delta.z -= 0.5f;
            break;
        
        case sf::Keyboard::S:
            delta.z += 0.5f;
            break;

        case sf::Keyboard::A:
            delta.x -= 0.5f;
            break;
        
        case sf::Keyboard::D:
            delta.x += 0.5f;
            break;

        case sf::Keyboard::Space:
            delta.y += 0.5f;
            break;
        
        case sf::Keyboard::LShift:
            delta.y -= 0.5f;
            break;
        
        default:
            break;
        }

        position_changed.emit(delta);
    }
};
