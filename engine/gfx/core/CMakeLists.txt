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

set (AEON_ENGINE_GFX_CORE_SOURCES
    include/aeon/gfx/gfx_atlas.h
    include/aeon/gfx/gfx_atlas_manager.h
    include/aeon/gfx/gfx_buffer.h
    include/aeon/gfx/gfx_buffer_manager.h
    include/aeon/gfx/gfx_camera.h
    include/aeon/gfx/gfx_device.h
    include/aeon/gfx/gfx_exception.h
    include/aeon/gfx/gfx_frame_listener.h
    include/aeon/gfx/gfx_material.h
    include/aeon/gfx/gfx_material_manager.h
    include/aeon/gfx/gfx_mesh.h
    include/aeon/gfx/gfx_render_target.h
    include/aeon/gfx/gfx_shader.h
    include/aeon/gfx/gfx_shader_manager.h
    include/aeon/gfx/gfx_texture.h
    include/aeon/gfx/gfx_texture_manager.h
    include/aeon/gfx/gfx_viewport.h
    src/gfx_atlas.cpp
    src/gfx_atlas_manager.cpp
    src/gfx_buffer.cpp
    src/gfx_buffer_manager.cpp
    src/gfx_camera.cpp
    src/gfx_device.cpp
    src/gfx_render_target.cpp
    src/gfx_shader.cpp
    src/gfx_viewport.cpp
)

source_group(gfx\\core FILES ${AEON_ENGINE_GFX_CORE_SOURCES})

add_library(aeon_engine_gfx_core STATIC
    ${AEON_ENGINE_GFX_CORE_SOURCES}
)

target_link_libraries(aeon_engine_gfx_core
    aeon_engine_common
    aeon_engine_data
    aeon_engine_resources
    aeon_logger
    glm
)

target_include_directories(aeon_engine_gfx_core
    PUBLIC include
)

set_target_properties(
    aeon_engine_gfx_core PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    FOLDER engine/gfx
)

install(
    TARGETS aeon_engine_gfx_core
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

install(
    DIRECTORY include/
    DESTINATION include
    FILES_MATCHING PATTERN "*.h"
)

