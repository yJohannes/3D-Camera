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

    explicit EventManager() = default;

    void add_callback(sf::Event::EventType event_type, Callback callback)
    {
        callbacks[event_type].push_back(callback);
    }

    void register_callback(const sf::Event& event)
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
    std::unordered_map<sf::Event::EventType, std::vector<Callback>> callbacks;
};