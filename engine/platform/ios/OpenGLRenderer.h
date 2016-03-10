 /*
 Copyright (C) 2015 Apple Inc. All Rights Reserved.
 See LICENSE.txt for this sample’s licensing information
 
 Abstract:
 The OpenGLRenderer class creates and draws objects.
  Most of the code is OS independent.
 */

#import <Foundation/Foundation.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>

@interface OpenGLRenderer : NSObject

@property (nonatomic) GLuint defaultFBOName;

- (instancetype) initWithDefaultFBO: (GLuint) defaultFBOName;
- (void) render;
- (void) dealloc;

@end
