#include "application/window.hpp"

int main()
{
    sf::ContextSettings context;
    context.depthBits = 24;
    context.antialiasingLevel = 0;

    MainWindow window(1200, 800, "Mandelbrot", context, sf::Style::Default);
    window.run();
    return 0;
}