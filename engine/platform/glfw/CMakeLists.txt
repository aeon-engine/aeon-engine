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

message(STATUS "+------------------------------------------------------------------------------+")
message(STATUS "| GLFW                                                                         |")
message(STATUS "+------------------------------------------------------------------------------+")
add_subdirectory(${AEON_ENGINE_ROOT}/dep/glfw dep/glfw)

set (AEON_ENGINE_PLATFORM_GLFW_SOURCES
    include/aeon/platform/glfw/glfw_platform_monitor.h
    include/aeon/platform/glfw/glfw_platform_window.h
    include/aeon/platform/glfw/glfw_platform_manager.h
    src/glfw_platform_monitor.cpp
    src/glfw_platform_window.cpp
    src/glfw_platform_manager.cpp
)

source_group(platform\\glfw FILES ${AEON_ENGINE_PLATFORM_GLFW_SOURCES})

add_library(aeon_engine_platform_glfw STATIC
    ${AEON_ENGINE_PLATFORM_GLFW_SOURCES}
)

target_link_libraries(aeon_engine_platform_glfw
    aeon_engine_platform_core
    aeon_logger
    glfw
    glm
)

target_include_directories(aeon_engine_platform_glfw
    PUBLIC include
)

set_target_properties(
    aeon_engine_platform_glfw PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    FOLDER engine/platform
)

install(
    TARGETS aeon_engine_platform_glfw
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

install(
    DIRECTORY include/
    DESTINATION include
    FILES_MATCHING PATTERN "*.h"
)
