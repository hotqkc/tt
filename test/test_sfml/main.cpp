
#include <SFML/Config.hpp>
#include <SFML/Window/WindowBase.hpp>
#include <SFML/Window/Event.hpp>

int main(int argc, char *argv[])
{
    // Create the main window
    sf::WindowBase window(sf::VideoMode(800, 600), "SFML window");
    
    uint64_t count = 0;
    
    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed: window.close(); break;
                default:break;
            }
        }
        count++;
    }
    
    return EXIT_SUCCESS;
}
