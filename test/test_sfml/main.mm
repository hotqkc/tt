
#include <SFML/Config.hpp>
#include <SFML/Window/WindowBase.hpp>
#include <SFML/Window/Event.hpp>

#include <SFML/Config.hpp>

//#ifdef SFML_SYSTEM_IOS

#include <UIKit/UIKit.h>


////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    // Note: we intentionally drop command line arguments,
    // there's no such thing as a command line on an iOS device :)
    
    // Important: "SFAppDelegate" must always match the name of the
    // application delegate class defined in sfml-window
    
    // Create the main window
//    sf::WindowBase window(sf::VideoMode(800, 600), "SFML window");
//
//    // Start the game loop
//    while (window.isOpen())
//    {
//        // Process events
//        sf::Event event;
//        while (window.pollEvent(event))
//        {
//            // Close window: exit
//            if (event.type == sf::Event::Closed)
//                window.close();
//        }
//    }
    return UIApplicationMain(argc, argv, nil, @"SFAppDelegate");
}

//#endif // SFML_SYSTEM_IOS
