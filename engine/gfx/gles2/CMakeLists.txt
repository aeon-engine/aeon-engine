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

set (AEON_ENGINE_GFX_GLES2_SOURCES
    include/aeon/gfx/gles2/gfx_gles2_buffer.h
    include/aeon/gfx/gles2/gfx_gles2_buffer_manager.h
    include/aeon/gfx/gles2/gfx_gles2_device.h
    include/aeon/gfx/gles2/gfx_gles2_material.h
    include/aeon/gfx/gles2/gfx_gles2_material_manager.h
    include/aeon/gfx/gles2/gfx_gles2_mesh.h
    include/aeon/gfx/gles2/gfx_gles2_shader.h
    include/aeon/gfx/gles2/gfx_gles2_shader_manager.h
    include/aeon/gfx/gles2/gfx_gles2_texture.h
    include/aeon/gfx/gles2/gfx_gles2_texture_manager.h
    src/gfx_gles2_buffer.cpp
    src/gfx_gles2_buffer_manager.cpp
    src/gfx_gles2_device.cpp
    src/gfx_gles2_material.cpp
    src/gfx_gles2_material_manager.cpp
    src/gfx_gles2_mesh.cpp
    src/gfx_gles2_shader.cpp
    src/gfx_gles2_shader_manager.cpp
    src/gfx_gles2_texture.cpp
    src/gfx_gles2_texture_manager.cpp
)

source_group(gfx\\gles2 FILES ${AEON_ENGINE_GFX_GLES2_SOURCES})

add_library(aeon_engine_gfx_gles2 STATIC
    ${AEON_ENGINE_GFX_GLES2_SOURCES}
)

target_link_libraries(aeon_engine_gfx_gles2
    aeon_engine_gfx_core
    aeon_engine_gfx_gl_common
    aeon_engine_input
)

target_include_directories(aeon_engine_gfx_gles2
    PUBLIC include
    PRIVATE ${CMAKE_BINARY_DIR}
)

if (AEON_PLATFORM_RPI)
    # Required for the gles 2 headers and library.
    target_link_libraries(aeon_engine_gfx_gles2
        RaspberryPiSdk
    )
endif ()

set_target_properties(
    aeon_engine_gfx_gles2 PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    FOLDER engine/gfx
)

install(
    TARGETS aeon_engine_gfx_gles2
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

install(
    DIRECTORY include/
    DESTINATION include
    FILES_MATCHING PATTERN "*.h"
)

