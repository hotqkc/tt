

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <bx/bx.h>

#include <SFML/Window/WindowBase.hpp>
#include <SFML/Config.hpp>
#include <SFML/Main.hpp>
#include <SFML/Window/Event.hpp>

#define SC_WIDTH 1280
#define SC_HEIGHT 720

int main(int argc, char * argv[]) {

     sf::WindowBase window(sf::VideoMode(SC_WIDTH, SC_HEIGHT), "SFML window");
    
    bgfx::init();
    
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {      

                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }
        }
        //printf("%d\n", bgfx::getRendererType());
    }

    return 0;
}
