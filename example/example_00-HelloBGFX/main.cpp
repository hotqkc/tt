
#include <SFML/Config.hpp>
#include <SFML/Window/WindowBase.hpp>
#include <SFML/Window/Event.hpp>

#include "cube.h"

#if defined(SXB_SYSTEM_IOS)
#include <SFML/Main.hpp>
#endif

int main(int argc, char *argv[])
 {
     // Create the main window
     sf::WindowBase window(sf::VideoMode(WNDW_WIDTH, WNDW_HEIGHT), "SFML window");

	 Cube exampleCube;
	 exampleCube.init(window.getWindowHandle());

	 uint64_t counter = 0;

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

		 exampleCube.update(counter);
		 counter++;
     }

     return EXIT_SUCCESS;
 }
