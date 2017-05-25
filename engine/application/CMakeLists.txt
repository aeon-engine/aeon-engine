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

set (AEON_ENGINE_APPLICATION_SOURCES
    include/aeon/application/context.h
    include/aeon/application/default_context.h
    include/aeon/application/base_application.h
    include/aeon/application/desktop_application.h
    src/default_context.cpp
    src/base_application.cpp
    src/desktop_application.cpp
)

source_group(application FILES ${AEON_ENGINE_APPLICATION_SOURCES})

add_library(aeon_engine_application STATIC
    ${AEON_ENGINE_APPLICATION_SOURCES}
)

target_link_libraries(aeon_engine_application
    aeon_engine_common
    aeon_engine_data
    aeon_engine_io
    aeon_engine_storage
    aeon_engine_resources
    aeon_engine_gfx_core
    aeon_engine_gfx_gl #TODO!
    aeon_engine_scene_core
    aeon_engine_basic_scene_manager #TODO!
    aeon_engine_assets
    aeon_engine_input
    aeon_engine_platform_core
    aeon_engine_platform_glfw #TODO!
    aeon_engine_codecs
    aeon_engine_codec_amf
    aeon_engine_codec_asc
    aeon_engine_codec_assimp
    aeon_engine_codec_ata
    aeon_engine_codec_dds
    aeon_engine_codec_png
    aeon_engine_codec_prg
)

target_include_directories(aeon_engine_application
    PUBLIC include
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

set_target_properties(
    aeon_engine_application PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    FOLDER engine
)

install(
    TARGETS aeon_engine_application
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

install(
    DIRECTORY include/
    DESTINATION include
    FILES_MATCHING PATTERN "*.h"
)
