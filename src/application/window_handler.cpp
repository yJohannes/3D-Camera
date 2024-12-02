// #include "window_handler.hpp"

// WindowHandler::WindowHandler(sf::RenderWindow &target_window)
//     : r_window(target_window)
//     , m_event_manager()
// {
//     init_events();
// }

// void WindowHandler::process_events()
// {
//     sf::Event event;
//     while (r_window.pollEvent(event))
//     {
//         m_event_manager.trigger_event_callbacks(event);
//     }
//     return;
// }