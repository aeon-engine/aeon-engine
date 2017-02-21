# Copyright (c) 2012-2017 Robin Degen
#
# Permission is hereby granted, free of charge, to any person
# obtaining a copy of this software and associated documentation
# files (the "Software"), to deal in the Software without
# restriction, including without limitation the rights to use,
# copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following
# conditions:
#
# The above copyright notice and this permission notice shall be
# included in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
# OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
# HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
# WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
# OTHER DEALINGS IN THE SOFTWARE.

include(Utility)
include(Buildinfo)

generate_build_info_header(${CMAKE_BINARY_DIR}/buildinfo.h)

add_subdirectory(serialization)
add_subdirectory(common)
add_subdirectory(data)
add_subdirectory(platform)
add_subdirectory(storage)
add_subdirectory(resources)
add_subdirectory(gfx)
add_subdirectory(scene)
add_subdirectory(assets)
add_subdirectory(input)

################################################################################

add_source_path(AEON_ENGINE_SOURCES application)

################################################################################

option(AEON_CONSOLE_OUTPUT_DEBUG_MSGS "Console outputs debug/trace messages." ON)
set(AEON_CONSOLE_BUFFER_SIZE 10240 CACHE STRING "The maximum length of a single console line")
set(AEON_DEFAULT_CONSOLE_LOG_LEVEL "console::log_level::info" CACHE STRING "The default minimum log level")
configure_file(build_config.h.in ${CMAKE_BINARY_DIR}/build_config.h @ONLY)

################################################################################

generate_source_groups("${AEON_ENGINE_SOURCES}")

add_library(aeon_engine STATIC ${AEON_ENGINE_SOURCES})

target_include_directories(aeon_engine
    PUBLIC ${CMAKE_BINARY_DIR}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(aeon_engine
    aeon_engine_common
    aeon_engine_data
    aeon_engine_platform
    aeon_engine_storage
    aeon_engine_resources
    aeon_engine_gfx_core
    aeon_engine_scene_core
    aeon_engine_basic_scene_manager
    aeon_engine_assets
    aeon_engine_input
    aeon
    glm
    ${OPENGL_LIBRARIES}
)

if (APPLE)
    target_link_libraries(aeon_engine ${COCOA_LIBRARY} ${IOKIT_LIBRARY} ${COREVIDEO_LIBRARY})
endif ()

if (AEON_GFX_GL)
    target_link_libraries(aeon_engine
        aeon_engine_gfx_gl_common
        aeon_engine_gfx_gl
    )
endif ()

if (AEON_GFX_GLES2)
    target_link_libraries(aeon_engine
        aeon_engine_gfx_gl_common
        aeon_engine_gfx_gles2
    )
endif ()

set_target_properties(
    aeon_engine PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    FOLDER engine
)

install(
    TARGETS aeon_engine
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

install(
    DIRECTORY application/
    DESTINATION include/application
    FILES_MATCHING PATTERN "*.h"
)

install(
    FILES
        ${CMAKE_BINARY_DIR}/build_config.h
        ${CMAKE_BINARY_DIR}/buildinfo.h
    DESTINATION include
)

install(
    FILES
        ${CMAKE_SOURCE_DIR}/dep/cmake/FindAeonEngine.cmake
    DESTINATION cmake
)
