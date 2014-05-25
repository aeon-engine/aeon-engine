#ifndef buildconfig_h__
#define buildconfig_h__

#define AEON_CONSOLE_OUTPUT_DEBUG_MSGS
#define AEON_CONSOLE_BUFFER_SIZE			(10 * 1024)
#define AEON_DEFAULT_CONSOLE_LOG_LEVEL		console::log_level::info

#define AEON_STREAM_MAX_TEXT_LINE_LENGTH	2048
#define AEON_STREAM_DEFAULT_NAME			"<UNNAMED>"

#define AEON_USE_PNG
#define AEON_USE_GLFW_PLATFORM

#define AEON_DEFAULT_SCREEN_WIDTH			1280
#define AEON_DEFAULT_SCREEN_HEIGHT			720

#define AEON_SHADER_ATTRIB_VERTEX_ID		0
#define AEON_SHADER_ATTRIB_VERTEX_NAME		"in_position"

#define AEON_SHADER_ATTRIB_TEXCOORD_ID		1
#define AEON_SHADER_ATTRIB_TEXCOORD_NAME	"in_texcoord0"

#define AEON_SHADER_MATRIX_NAME				"in_matrix"
#define AEON_SHADER_TEXTURE0_NAME			"in_texture0"
#define AEON_SHADER_COLOR_NAME				"in_color"

#endif // buildconfig_h__
