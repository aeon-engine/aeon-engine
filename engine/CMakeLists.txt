include(Common)

################################################################################

add_source_path(AEON_ENGINE_SOURCES common)
add_source_path(AEON_ENGINE_SOURCES common/types)
add_source_path(AEON_ENGINE_SOURCES console)
add_source_path(AEON_ENGINE_SOURCES resources)
add_source_path(AEON_ENGINE_SOURCES resources/codecs)
add_source_path(AEON_ENGINE_SOURCES resources/providers)
add_source_path(AEON_ENGINE_SOURCES resources/wrappers)

################################################################################

add_source_path(AEON_ENGINE_SOURCES gfx)

if (AEON_GFX_GL)
    add_source_path(AEON_ENGINE_SOURCES gfx/gl)
endif ()

################################################################################

add_source_path(AEON_ENGINE_SOURCES platform)
add_source_path(AEON_ENGINE_SOURCES platform/generic)

if (AEON_PLATFORM_GLFW)
    add_source_path(AEON_ENGINE_SOURCES platform/glfw)
endif ()

################################################################################

add_source_path(AEON_ENGINE_SOURCES scene)
add_source_path(AEON_ENGINE_SOURCES scene/scene_managers/basic)
add_source_path(AEON_ENGINE_SOURCES scene/scene_managers/octree)

################################################################################

option(AEON_CONSOLE_OUTPUT_DEBUG_MSGS "Console outputs debug/trace messages." ON)
set(AEON_CONSOLE_BUFFER_SIZE 10240 CACHE STRING "The maximum length of a single console line")
set(AEON_DEFAULT_CONSOLE_LOG_LEVEL "console::log_level::info" CACHE STRING "The default minimum log level")
configure_file(build_config.h.in build_config.h @ONLY)

################################################################################

generate_source_groups("${AEON_ENGINE_SOURCES}")

add_library(aeon_engine STATIC ${AEON_ENGINE_SOURCES})

target_include_directories(aeon_engine
    PRIVATE ${CMAKE_CURRENT_BINARY_DIR}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    PUBLIC ${ASSIMP_INCLUDE_DIRS}
)

target_link_libraries(aeon_engine
    aeon
    glfw
    glew_s
    glm
    png_static
    ${ASSIMP_LIBRARIES}
    ${OPENGL_LIBRARIES}
)

if (APPLE)
    target_link_libraries(aeon_engine ${COCOA_LIBRARY} ${IOKIT_LIBRARY} ${COREVIDEO_LIBRARY})
endif ()

set_target_properties(
    aeon_engine PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    FOLDER engine
)