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

option(AEON_BUILD_GFX_GL "Build the OpenGL 3.3 subsystem" ON)
option(AEON_BUILD_GFX_GLES "Build the OpenGLES 2.0 subsystem" OFF)

option(AEON_BUILD_PLATFORM_GLFW "Build the GLFW subsystem" ON)
option(AEON_BUILD_PLATFORM_SDL "Build the SDL subsystem" ON)
option(AEON_BUILD_PLATFORM_RPI "Build the Raspberry Pi subsystem" OFF)

if (AEON_BUILD_GFX_GL AND AEON_BUILD_GFX_GLES)
    message (FATAL_ERROR "Currently building both GL and GLES 2.0 isn't supported. Please select one.")
endif ()

if (AEON_BUILD_GFX_GL)
    set(AEON_GFX_GL ON)
endif ()

if (AEON_BUILD_GFX_GLES)
    set(AEON_GFX_GLES2 ON)
endif ()

set(AEON_DEFAULT_WINDOW_WIDTH 1280 CACHE STRING "Default window width if none was given in the config file.")
set(AEON_DEFAULT_WINDOW_HEIGHT 720 CACHE STRING "Default window height if none was given in the config file.")
set(AEON_DEFAULT_WINDOW_TITLE "Aeon Engine" CACHE STRING "Default window title if none was given in the config file.")
set(AEON_CONFIG_FILE_NAME "config.conf" CACHE STRING "Config file name.")
set(AEON_DEFAULT_LOG_LEVEL "aeon::logger::log_level::message" CACHE STRING "The default minimum log level")
configure_file(build_config.h.in ${CMAKE_BINARY_DIR}/build_config.h @ONLY)

################################################################################

generate_build_info_header(${CMAKE_BINARY_DIR}/buildinfo.h)

add_subdirectory(serialization)
add_subdirectory(common)
add_subdirectory(data)
add_subdirectory(io)
add_subdirectory(storage)
add_subdirectory(resources)
add_subdirectory(codecs)
add_subdirectory(gfx)
add_subdirectory(scene)
add_subdirectory(assets)
add_subdirectory(input)
add_subdirectory(platform)
add_subdirectory(application)

################################################################################

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
