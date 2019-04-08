
#include <Config.hpp>
#include <Window/WindowBase.hpp>
#include <Window/Event.hpp>
#include <bgfx/platform.h>
#include <bx/bx.h>
#include <bx/math.h>

#include <sxbCommon/utils.h>
#include "stencil.h"

int main(int argc, char *argv[])
 {
     // Create the main window
     tinySFML::WindowBase window(tinySFML::VideoMode(WNDW_WIDTH, WNDW_HEIGHT), "SFML window");
	 stencil exampleStencil;
	 exampleStencil.init(window.getSystemHandle());

	 uint64_t count = 0;

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

		 exampleStencil.update(count);
		 count++;
     }

     return EXIT_SUCCESS;
 }