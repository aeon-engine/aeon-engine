/*
 Copyright (C) 2015 Apple Inc. All Rights Reserved.
 See LICENSE.txt for this sample’s licensing information
 
 Abstract:
 The OpenGLRenderer class creates and draws objects.
  Most of the code is OS independent.
 */

#import "OpenGLRenderer.h"
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

@interface OpenGLRenderer ()
{
    GLuint _viewWidth;
    GLuint _viewHeight;
    GLuint _defaultFBOName;
}
@end

@implementation OpenGLRenderer


- (void) resizeWithWidth:(GLuint)width AndHeight:(GLuint)height
{
	glViewport(0, 0, width, height);

	_viewWidth = width;
	_viewHeight = height;
}

- (id) initWithDefaultFBO: (GLuint) defaultFBOName
{
	if((self = [super init]))
	{
		NSLog(@"%s %s", glGetString(GL_RENDERER), glGetString(GL_VERSION));
		
		////////////////////////////////////////////////////
		// Build all of our and setup initial state here  //
		// Don't wait until our real time run loop begins //
		////////////////////////////////////////////////////
		
		_defaultFBOName = defaultFBOName;
		
		_viewWidth = 100;
		_viewHeight = 100;

		////////////////////////////////////////////////
		// Set up OpenGL state that will never change //
		////////////////////////////////////////////////
		
		// Depth test will always be enabled
		//glEnable(GL_DEPTH_TEST);
	
		// We will always cull back faces for better performance
		//glEnable(GL_CULL_FACE);
		
		// Always use this clear color
		//glClearColor(0.5f, 0.4f, 0.5f, 1.0f);
		
		// Draw our scene once without presenting the rendered image.
		//   This is done in order to pre-warm OpenGL
		// We don't need to present the buffer since we don't actually want the 
		//   user to see this, we're only drawing as a pre-warm stage
		[self render];
	}
	
	return self;
}


- (void) render
{
    // ?
}

- (void) dealloc
{
}

@end
