include(Utility)
include(Buildinfo)

################################################################################

add_source_path(AEON_ENGINE_SOURCES common)
add_source_path(AEON_ENGINE_SOURCES common/types)
add_source_path(AEON_ENGINE_SOURCES application)
add_source_path(AEON_ENGINE_SOURCES resources)
add_source_path(AEON_ENGINE_SOURCES resources/codecs)
add_source_path(AEON_ENGINE_SOURCES resources/providers)
add_source_path(AEON_ENGINE_SOURCES resources/wrappers)

################################################################################

add_source_path(AEON_ENGINE_SOURCES gfx)

if (AEON_GFX_GL)
    add_source_path(AEON_ENGINE_SOURCES gfx/gl)
endif ()

if (AEON_GFX_GLES2)
    add_source_path(AEON_ENGINE_SOURCES gfx/gles2)
endif ()

################################################################################

add_source_path(AEON_ENGINE_SOURCES platform)
add_source_path(AEON_ENGINE_SOURCES platform/generic)

if (AEON_PLATFORM_GLFW)
    add_source_path(AEON_ENGINE_SOURCES platform/glfw)
endif ()

if (AEON_PLATFORM_RPI)
    add_source_path(AEON_ENGINE_SOURCES platform/rpi)
endif ()

if (AEON_PLATFORM_IOS)
    add_source_path(AEON_ENGINE_SOURCES platform/ios)
endif ()

################################################################################

add_source_path(AEON_ENGINE_SOURCES scene)
add_source_path(AEON_ENGINE_SOURCES scene/scene_managers/basic)
add_source_path(AEON_ENGINE_SOURCES scene/scene_managers/octree)

################################################################################
set(AEON_DEFAULT_WINDOW_WIDTH_HINT 800 CACHE STRING "Window width hint. This may be ignored on certain platforms.")
set(AEON_DEFAULT_WINDOW_HEIGHT_HINT 600 CACHE STRING "Window height hint. This may be ignored on certain platforms.")
set(AEON_DEFAULT_WINDOW_TITLE_HINT "Aeon Engine" CACHE STRING "Window title hint. This may be ignored on certain platforms.")

option(AEON_CONSOLE_OUTPUT_DEBUG_MSGS "Console outputs debug/trace messages." ON)
set(AEON_CONSOLE_BUFFER_SIZE 10240 CACHE STRING "The maximum length of a single console line")
set(AEON_DEFAULT_CONSOLE_LOG_LEVEL "console::log_level::info" CACHE STRING "The default minimum log level")

configure_file(build_config.h.in build_config.h @ONLY)

################################################################################

generate_build_info_header(${CMAKE_CURRENT_BINARY_DIR}/buildinfo.h)

################################################################################

generate_source_groups("${AEON_ENGINE_SOURCES}")

add_library(aeon_engine STATIC ${AEON_ENGINE_SOURCES})

target_include_directories(aeon_engine
    PUBLIC ${CMAKE_CURRENT_BINARY_DIR}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    PUBLIC ${ASSIMP_INCLUDE_DIRS}
)

target_link_libraries(aeon_engine
    aeon
    glm
    png_static
    openal
    ogg
    vorbis
    freetype
    ${ASSIMP_LIBRARIES}
    ${OPENGL_LIBRARIES}
)

if (APPLE)
    target_link_libraries(aeon_engine ${COCOA_LIBRARY} ${IOKIT_LIBRARY} ${COREVIDEO_LIBRARY})
endif ()

if (AEON_GFX_GL)
    target_link_libraries(aeon_engine glew_s)
endif ()

if (AEON_PLATFORM_GLFW)
    target_link_libraries(aeon_engine glfw)
endif ()

if (AEON_PLATFORM_RPI)
    target_link_libraries(aeon_engine RaspberryPiSdk)
endif ()

set_target_properties(
    aeon_engine PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    FOLDER engine
)

