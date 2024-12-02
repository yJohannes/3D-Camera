#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include <unordered_map>
#include <vector>

#include "signal.hpp"

class EventManager
{
public:
    using Callback = std::function<void(sf::Event)>;
    using EventType = sf::Event::EventType;

    explicit EventManager() = default;

    void add_callback(EventType event_type, Callback callback)
    {
        callbacks[event_type].push_back(callback);
    }

    template <typename Obj>
    void add_callback(EventType event_type, Obj *obj, void (Obj::*event_handler)(const sf::Event&))
    {
        add_callback(event_type, [obj, event_handler](const sf::Event& event) {
            (obj->*event_handler)(event);
        });
    }

    void trigger_event_callbacks(const sf::Event& event)
    {
        if (callbacks.find(event.type) != callbacks.end())
        {
            for (auto& callback : callbacks[event.type])
            {
                callback(event);
            }
        }
    }

private:
    std::unordered_map<EventType, std::vector<Callback>> callbacks;
};