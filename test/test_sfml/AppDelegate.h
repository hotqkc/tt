//
//  AppDelegate.h
//  Test1
//
//  Created by quku on 2019/3/15.
//  Copyright © 2019 quku. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <UIKit/UIApplication.h> // UIApplicationDelegate
#include "ViewController.h"

@interface AppDelegate : UIResponder <UIApplicationDelegate>

@property (strong, nonatomic) UIWindow *window;
@property (strong, nonatomic) ViewController *vc;

@end
