#include "application/window.hpp"

int main()
{
    sf::ContextSettings context;
    context.depthBits = 24;
    context.stencilBits = 8;
    context.antialiasingLevel = 4;

    MainWindow window(1200, 800, "3D Camera", context, sf::Style::Default);
    window.run();
    return 0;
}