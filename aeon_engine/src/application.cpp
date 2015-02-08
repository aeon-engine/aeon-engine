/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2014 Robin Degen
 * All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains the property of
 * Robin Degen and its suppliers, if any. The intellectual and technical
 * concepts contained herein are proprietary to Robin Degen and its suppliers
 * and may be covered by U.S. and Foreign Patents, patents in process, and are
 * protected by trade secret or copyright law. Dissemination of this
 * information or reproduction of this material is strictly forbidden unless
 * prior written permission is obtained from Robin Degen.
 */

#include "stdafx.h"

#include "application.h"
#include "rpggame.h"

namespace aeon
{

application::application() :
    platform_(nullptr)
{

}

application::~application()
{
    if (platform_)
        delete platform_;

    platform_ = nullptr;
}

material_ptr mat;

void application::main(int argc, char *argv[])
{
    __setup_console();

    configfile config_file;
    config_file.load(std::make_shared<aeon::file_stream>
        ("config.ini", aeon::stream::access_mode::read));

    root::initialize(std::make_shared<aeon::platforms::glfw>());

    // Register us as a frame listener
    root::get_singleton().add_frame_listener(this);

    mat = material_manager::get_singleton().load("resources/materials/testmaterial.mat");

	file_stream_ptr file = std::make_shared<file_stream>("resources/scenes/testscene2.dae", file_stream::access_mode::read);
	scene_codec_manager::get_singleton().decode("ASSIMP", file);

    // Enter the main loop
    root::get_singleton().run();
}

bool application::on_frame(float dt)
{
    return true;
}

void perspectiveGL(GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar)
{

    const GLdouble pi = 3.1415926535897932384626433832795;
    GLdouble fW, fH;
    fH = tan((fovY / 2) / 180 * pi) * zNear;
    fH = tan(fovY / 360 * pi) * zNear;
    fW = fH * aspect;
    glFrustum(-fW, fW, -fH, fH, zNear, zFar);
}

void DemoLight(void)
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);

    // Light model parameters:
    // -------------------------------------------

    GLfloat lmKa[] = { 0.0, 0.0, 0.0, 0.0 };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmKa);

    glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1.0);
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 0.0);

    // -------------------------------------------
    // Spotlight Attenuation

    GLfloat spot_direction[] = { 1.0, -1.0, -1.0 };
    GLint spot_exponent = 30;
    GLint spot_cutoff = 180;

    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
    glLighti(GL_LIGHT0, GL_SPOT_EXPONENT, spot_exponent);
    glLighti(GL_LIGHT0, GL_SPOT_CUTOFF, spot_cutoff);

    GLfloat Kc = 1.0;
    GLfloat Kl = 0.0;
    GLfloat Kq = 0.0;

    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, Kc);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, Kl);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, Kq);


    // ------------------------------------------- 
    // Lighting parameters:

    GLfloat light_pos[] = { 0.0f, 0.0f, 5.0f, 1.0f };
    GLfloat light_Ka[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    GLfloat light_Kd[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat light_Ks[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_Ka);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_Kd);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_Ks);

    // -------------------------------------------
    // Material parameters:

    GLfloat material_Ka[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    GLfloat material_Kd[] = { 0.4f, 0.4f, 0.5f, 1.0f };
    GLfloat material_Ks[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat material_Ke[] = { 0.0f, 0.0f, 0.0f, 0.0f };
    GLfloat material_Se = 128.0f;

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_Ka);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_Kd);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_Ks);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, material_Ke);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material_Se);
}


float pos = 0.0f;
bool application::on_render()
{
    //glViewport(0, 0, 1280, 720);						// Reset The Current Viewport

    glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
    glLoadIdentity();									// Reset The Projection Matrix

    // Calculate The Aspect Ratio Of The Window
    perspectiveGL(45.0f, (GLfloat)1280 / (GLfloat)720, 0.1f, 100.0f);

    glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping ( NEW )
    glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
    glClearColor(1.0f, 0.0f, 1.0f, 0.5f);				// Black Background
    glClearDepth(1.0f);									// Depth Buffer Setup
    glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
    glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

    glEnable(GL_LIGHTING);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);         // Clear Screen And Depth Buffer
    
    glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
    glLoadIdentity();                           // Reset The Current Matrix
    glTranslatef(0.0f, 0.0f, -5.0f);                      // Move Into The Screen 5 Units
    glRotatef(20, 1, 0, 0);
    glRotatef(20, 0, 1, 0);

    /*GLfloat LightAmbient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat LightPosition[] = { 0.0f, 0.0f, pos, 1.0f };

    pos += 0.01f;
    glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);		// Setup The Ambient Light
    glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);		// Setup The Diffuse Light
    glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);	// Position The Light
    glEnable(GL_LIGHT1);								// Enable Light One*/

    DemoLight();

    mat->shader_resource->bind();

    /*glEnable(GL_PROGRAM_POINT_SIZE);
    glPointSize(10);

    glColor3f(1, 0, 0);
    glBegin(GL_POINTS);
        glVertex3fv(LightPosition);
    glEnd();*/


    glColor3f(1, 1, 1);
    glBegin(GL_QUADS);
    // Front Face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);  // Top Left Of The Texture and Quad
    // Back Face
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);  // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);  // Bottom Left Of The Texture and Quad
    // Top Face
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);  // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);  // Top Right Of The Texture and Quad
    // Bottom Face
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);  // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);  // Bottom Right Of The Texture and Quad
    // Right face
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);  // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);  // Bottom Left Of The Texture and Quad
    // Left Face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);  // Top Left Of The Texture and Quad
    glEnd();

    return true;
}

void application::__setup_console()
{
    //Set up debug logging
    aeon::console::set_loglevel(aeon::console::log_level::debug);

    //Create console streams
    auto console_stdoutput = std::make_shared<aeon::io_stream>
        (aeon::stream::access_mode::write);
    auto console_fileoutput = std::make_shared<aeon::file_stream>
        ("console.log", aeon::stream::access_mode::write);

    //Create listeners with these streams
    auto console_std_listener =
        std::make_shared<aeon::console_stream_listener>(console_stdoutput);
    auto console_file_listener =
        std::make_shared<aeon::console_stream_listener>(console_fileoutput);

    //Bind a default console
    aeon::console::add_console_listener(console_std_listener);
    aeon::console::add_console_listener(console_file_listener);
}

} /* namespace aeon */
