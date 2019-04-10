
#include <SFML/Config.hpp>
#include <SFML/Window/WindowBase.hpp>
#include <SFML/Window/Event.hpp>

#include <SFML/Config.hpp>

#import <UIKit/UIKit.h>

#include <SFML/Window/iOS/SFAppDelegate.hpp>

#include "AppDelegate.h"

int main(int argc, char * argv[]) {
    @autoreleasepool {
        //return UIApplicationMain(argc, argv, nil, @"SFAppDelegate");
        return UIApplicationMain(argc, argv, nil, NSStringFromClass([SFAppDelegate class]));
    }
}
