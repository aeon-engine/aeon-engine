/*
 Copyright (C) 2015 Apple Inc. All Rights Reserved.
 See LICENSE.txt for this sample’s licensing information
 
 Abstract:
 The application delegate
 */


#import <UIKit/UIKit.h>
#import "ViewController.h"

@class EAGLView;
@class MainViewController;

@interface AppDelegate : NSObject <UIApplicationDelegate> {
    GLViewController *controller;
    EAGLView *glView;
}

@property (nonatomic, retain) UIWindow *window;

@end

