
#include <SFML/Config.hpp>
#include <SFML/Window/WindowBase.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Main.hpp>

#import <UIKit/UIKit.h>

#include "cube.h"

int main(int argc, char *argv[])
 {
     // Create the main window
     sf::WindowBase window(sf::VideoMode(WNDW_WIDTH, WNDW_HEIGHT), "SFML window");
//     NSString *resourceBundle = [[NSBundle mainBundle] pathForResource:@"MetalShaders" ofType:@"xcassets"];
//         NSLog(@"resourceBundle: %@", resourceBundle);
//         NSString *earth = [[NSBundlebundleWithPath:resourceBundle] pathForResource:@"Matthijs"ofType:@"jpg"inDirectory:@"Images/MoreImages"];
//
//         NSLog(@"path: %@", earth);

     NSString * bundlePath = [[ NSBundle mainBundle] pathForResource: @ "Settings" ofType :@ "bundle"];
//     NSBundle *resourceBundle = [NSBundle bundleWithPath:bundlePath];
//     NSString *path = [resourceBundle pathForResource :@"vs_cubes.bin" ofType :@""];
     
    //NSString *imagePath = [bundle pathForResource:@"0002" ofType:@"JPG"];
    //UIImageView *imageView = [[UIImageView alloc] initWithImage:[UIImage imageNamed:imagePath]];
   // [self.view addSubview:imageView];
     
	 Cube exampleCube;
	 exampleCube.init(window.getMetalHandle(), [bundlePath UTF8String]);

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
