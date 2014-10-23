#ifndef buildconfig_h__
#define buildconfig_h__

/************************************************************************/
/* Build options                                                        */
/************************************************************************/

/*!
* Define if Aeon should have support for loading PNG files
*/
#define AEON_USE_PNG

/*!
* Define if Aeon should have support for using GLFW as a platform
*/
#define AEON_USE_GLFW_PLATFORM

/*!
* Define if Aeon should have support for using the 
* Open Asset Import Library (Assimp)
*/
#define AEON_USE_ASSIMP

/************************************************************************/
/* Default settings                                                     */
/************************************************************************/

/*!
* The default horizontal resolution
*/
#define AEON_DEFAULT_SCREEN_WIDTH           1280

/*!
* The default vertical resolution
*/
#define AEON_DEFAULT_SCREEN_HEIGHT          720

/************************************************************************/
/* Console                                                              */
/************************************************************************/

/*!
 * Define if Aeon should log debug messages.
 */
#define AEON_CONSOLE_OUTPUT_DEBUG_MSGS

/*!
 * The maximum length of a single console line
 */
#define AEON_CONSOLE_BUFFER_SIZE            (10 * 1024)

/*!
 * The default minimum log level
 */
#define AEON_DEFAULT_CONSOLE_LOG_LEVEL      console::log_level::info

/************************************************************************/
/* Streams                                                              */
/************************************************************************/

/*!
 * The maximum length of a line read in a stream. If the line is longer, the
 * line will be truncated into seemingly multiple lines.
 */
#define AEON_STREAM_MAX_TEXT_LINE_LENGTH    2048

/*!
 * The default name of a stream. A stream in Aeon can have a name, which for
 * example in case of a FileStream, holds the name of the opened file. This
 * is useful for logging and debugging purposes.
 */
#define AEON_STREAM_DEFAULT_NAME            "<UNNAMED>"

/************************************************************************/
/* Materials                                                            */
/************************************************************************/

/*!
 * The maximum number of textures that can be bound from a material
 * for use in a shader.
 * TODO: glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &texture_units);
 */
#define AEON_MATERIAL_MAX_TEXTURE_BINDS     8

/*!
 * The default ambient RGBA reflectance of a material.
 * These are the OpenGL default values for GL_AMBIENT
 */
#define AEON_MATERIAL_DEFAULT_AMBIENT       0.2, 0.2, 0.2, 1.0

/*!
 * The default diffuse RGBA reflectance of a material.
 * These are the OpenGL default values for GL_DIFFUSE
 */
#define AEON_MATERIAL_DEFAULT_DIFFUSE       0.8, 0.8, 0.8, 1.0

/*!
* The default specular RGBA reflectance of a material.
* These are the OpenGL default values for GL_SPECULAR
*/
#define AEON_MATERIAL_DEFAULT_SPECULAR      0.0, 0.0, 0.0, 1.0

/*!
* The default RGBA emitted light intensity of a material.
* These are the OpenGL default values for GL_EMISSION
*/
#define AEON_MATERIAL_DEFAULT_EMISSION      0.0, 0.0, 0.0, 1.0

/*!
* The default RGBA specular exponent of a material.
* This is the OpenGL default value for GL_SHININESS
*/
#define AEON_MATERIAL_DEFAULT_SHININESS     0

/************************************************************************/
/* Shaders                                                              */
/************************************************************************/

/*!
 * The OpenGL attribute ID for vertex data
 */
#define AEON_SHADER_ATTRIB_VERTEX_ID        0

/*!
 * The OpenGL GLSL attribute name for vertex data
 */
#define AEON_SHADER_ATTRIB_VERTEX_NAME      "in_position"

/*!
 * The OpenGL attribute ID for texcoord data
 */
#define AEON_SHADER_ATTRIB_TEXCOORD_ID      1

/*!
 * The OpenGL GLSL attribute name for vertex data
 */
#define AEON_SHADER_ATTRIB_TEXCOORD_NAME    "in_texcoord0"

/*!
 * The OpenGL GLSL name for the render matrix
 */
#define AEON_SHADER_MATRIX_NAME             "in_matrix"

/*!
 * The OpenGL GLSL name for material texture0 (the main diffuse texture map)
 */
#define AEON_SHADER_TEXTURE0_NAME           "in_texture0"

/*!
 * The OpenGL GLSL name for the material color
 */
#define AEON_SHADER_COLOR_NAME              "in_color"

#endif /* buildconfig_h__ */
