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

find_package(OpenGL REQUIRED)

message(STATUS "+------------------------------------------------------------------------------+")
message(STATUS "| GLEW                                                                         |")
message(STATUS "+------------------------------------------------------------------------------+")
add_subdirectory(${AEON_ENGINE_ROOT}/dep/glew dep/glew)

set (AEON_ENGINE_GFX_GL_SOURCES
    include/aeon/gfx/gl/gfx_gl_buffer.h
    include/aeon/gfx/gl/gfx_gl_buffer_manager.h
    include/aeon/gfx/gl/gfx_gl_device.h
    include/aeon/gfx/gl/gfx_gl_material.h
    include/aeon/gfx/gl/gfx_gl_material_manager.h
    include/aeon/gfx/gl/gfx_gl_mesh.h
    include/aeon/gfx/gl/gfx_gl_shader.h
    include/aeon/gfx/gl/gfx_gl_shader_manager.h
    include/aeon/gfx/gl/gfx_gl_texture.h
    include/aeon/gfx/gl/gfx_gl_texture_manager.h
    include/aeon/gfx/gl/gfx_gl_vertex_array_object.h
    src/gfx_gl_buffer.cpp
    src/gfx_gl_buffer_manager.cpp
    src/gfx_gl_device.cpp
    src/gfx_gl_material.cpp
    src/gfx_gl_material_manager.cpp
    src/gfx_gl_mesh.cpp
    src/gfx_gl_shader.cpp
    src/gfx_gl_shader_manager.cpp
    src/gfx_gl_texture.cpp
    src/gfx_gl_texture_manager.cpp
    src/gfx_gl_vertex_array_object.cpp
)

source_group(gfx\\gl FILES ${AEON_ENGINE_GFX_GL_SOURCES})

add_library(aeon_engine_gfx_gl STATIC
    ${AEON_ENGINE_GFX_GL_SOURCES}
)

target_link_libraries(aeon_engine_gfx_gl
    aeon_engine_gfx_core
    aeon_engine_gfx_gl_common
    glew_s
    aeon_logger
    glm
)

target_include_directories(aeon_engine_gfx_gl
    PUBLIC include
    PRIVATE ${CMAKE_BINARY_DIR}
)

set_target_properties(
    aeon_engine_gfx_gl PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    FOLDER engine/gfx
)

install(
    TARGETS aeon_engine_gfx_gl
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

install(
    DIRECTORY include/
    DESTINATION include
    FILES_MATCHING PATTERN "*.h"
)

