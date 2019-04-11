
#include <SFML/Config.hpp>
#include <SFML/Window/WindowBase.hpp>
#include <SFML/Window/Event.hpp>

#include <SFML/Config.hpp>

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <bx/bx.h>

#include <SFML/Main.hpp>

//#include <UIKit/UIKit.h>
//#include <SFML/Window/iOS/SFAppDelegate.hpp>

#define SC_WIDTH 1280
#define SC_HEIGHT 720

int main(int argc, char * argv[]) {
    
    sf::WindowBase window(sf::VideoMode(SC_WIDTH, SC_HEIGHT), "SFML window");
    
    //[[SFAppDelegate getInstance] sfWindow];
    
    //NSLog(@"%d", bgfx::getRendererType());
    bgfx::PlatformData pd;
    pd.nwh = window.getSystemHandle();
//    pd.nwh = [[SFAppDelegate getInstance] sfWindow]->getSystemHandle();
    bgfx::setPlatformData(pd);

    bgfx::Init bgfxInit;
    bgfxInit.type = bgfx::RendererType::Count; // Automatically choose a renderer.
    bgfxInit.resolution.width = SC_WIDTH;
    bgfxInit.resolution.height = SC_HEIGHT;
    //bgfxInit.resolution.reset = BGFX_RESET_VSYNC;
    bgfx::init(bgfxInit);

    bgfx::setDebug(BGFX_DEBUG_TEXT);

    bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x443355FF, 1.0f, 0);
    bgfx::setViewRect(0, 0, 0, SC_WIDTH, SC_HEIGHT);
//    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
//            else if (event.type == sf::Event::TouchBegan ||
//                     event.type == sf::Event::TouchMoved ||
//                     event.type == sf::Event::TouchEnded)
//                NSLog(@"(%d, %d)", event.touch.x, event.touch.y);
        }
//        bgfx::touch(0);
//        bgfx::frame();
    }
    
    return 0;
}
