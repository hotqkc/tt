//
//  ViewController.m
//  Test1
//
//  Created by quku on 2019/3/15.
//  Copyright © 2019 quku. All rights reserved.
//
#import "CppInterface.h"
#import "ViewController.h"

@interface AAViewController ()
{
        CppInterface* i;
}

@end

@implementation AAViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
        i = [[CppInterface alloc]init];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
