# Copyright (c) 2012-2018 Robin Degen
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

# Check and log all OpenGL 3 and GLES 2 errors. Warning: This is very slow,
# only use for debugging purposes.
option(AEON_ENABLE_GL_ERROR_CHECKS "Check and log all OpenGL 3 and GLES 2 errors." ON)

set (AEON_ENGINE_GFX_GL_COMMON_SOURCES
    include/aeon/gfx/gl_common/check_gl_error.h
    src/check_gl_error.cpp
)

source_group(gfx\\core FILES ${AEON_ENGINE_GFX_GL_COMMON_SOURCES})

add_library(aeon_engine_gfx_gl_common STATIC
    ${AEON_ENGINE_GFX_GL_COMMON_SOURCES}
)

target_link_libraries(aeon_engine_gfx_gl_common
    aeon_engine_common
    aeon_engine_gfx_core
    aeon_logger
)

target_include_directories(aeon_engine_gfx_gl_common
    PUBLIC include
    PRIVATE ${CMAKE_BINARY_DIR}
)

if (AEON_GFX_GL)
    target_link_libraries(aeon_engine_gfx_gl_common
        glew_s
    )
endif ()

if (AEON_PLATFORM_RPI)
    target_include_directories(aeon_engine_gfx_gl_common
        PRIVATE ${RASPBERRY_PI_INCLUDE_PATHS}
    )

    target_link_libraries(aeon_engine_gfx_gl_common
        ${RASPBERRY_PI_LIBRARIES}
    )
endif ()

set_target_properties(
    aeon_engine_gfx_gl_common PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    FOLDER engine/gfx
)

install(
    TARGETS aeon_engine_gfx_gl_common
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

install(
    DIRECTORY include/
    DESTINATION include
    FILES_MATCHING PATTERN "*.h"
)

