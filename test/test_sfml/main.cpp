
#include <SFML/Config.hpp>
#include <SFML/Window/WindowBase.hpp>
#include <SFML/Window/Event.hpp>

//#include <bgfx/bgfx.h>
//#include <bgfx/platform.h>
//#include <bx/bx.h>

#define WNDW_WIDTH 800
#define WNDW_HEIGHT 600

int main(int argc, char *argv[])
{
    // Create the main window
    sf::WindowBase window(sf::VideoMode(800, 600), "SFML window");
    
//    bgfx::PlatformData pd;
//    pd.nwh = window.getSystemHandle();
//    bgfx::setPlatformData(pd);
//
//    bgfx::Init bgfxInit;
//    bgfxInit.type = bgfx::RendererType::Count; // Automatically choose a renderer.
//    bgfxInit.resolution.width = WNDW_WIDTH;
//    bgfxInit.resolution.height = WNDW_HEIGHT;
//    bgfxInit.resolution.reset = BGFX_RESET_VSYNC;
//    bgfx::init(bgfxInit);
    
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
