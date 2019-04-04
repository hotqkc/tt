
#include <Config.hpp>
#include <Window/WindowBase.hpp>
#include <Window/Event.hpp>

#include "lod.h"

int main(int argc, char *argv[])
 {
     // Create the main window
     tinySFML::WindowBase window(tinySFML::VideoMode(WNDW_WIDTH, WNDW_HEIGHT), "SFML window");
	 lod exampleLod;
	 exampleLod.init( window.getSystemHandle() );

	 unsigned int counter = 0;

     // Start the game loop
     while (window.isOpen())
     {
         // Process events
		 tinySFML::Event event;
         while (window.pollEvent(event))
         {
             // Close window: exit
             if (event.type == tinySFML::Event::Closed)
                 window.close();
         }

		 exampleLod.update();

		 counter++;

     }

     return EXIT_SUCCESS;
 }