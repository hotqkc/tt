

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <bx/bx.h>

#include <SFML/Window/WindowBase.hpp>
#include <SFML/Config.hpp>
#include <SFML/Main.hpp>
#include <SFML/Window/Event.hpp>

#define SC_WIDTH 1334
#define SC_HEIGHT 750

#include <UIKit/UIKit.h>

int main(int argc, char * argv[]) {
    sf::WindowBase window(sf::VideoMode(SC_WIDTH, SC_HEIGHT), "SFML Widnow");
    
    //bgfx::init();
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if(event.type == sf::Event::TouchBegan)
                NSLog(@"%d, %d", event.touch.x, event.touch.y);
        }
    }
    return 0;
}
