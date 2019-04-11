
#include <SFML/Config.hpp>
#include <SFML/Window/WindowBase.hpp>
#include <SFML/Window/Event.hpp>

#include <SFML/Config.hpp>

#import <UIKit/UIKit.h>

#include <SFML/Window/iOS/SFAppDelegate.hpp>

#include <SFML/Main.hpp>

#include "AppDelegate.h"

int main(int argc, char * argv[]) {
    
    sf::WindowBase window(sf::VideoMode(800, 600), "SFML window");

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }
    
    return 0;
}
