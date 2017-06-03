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

set (AEON_ENGINE_ASSET_SOURCES
    include/aeon/assets/asset_manager.h
    src/asset_manager.cpp
)

source_group(assets FILES ${AEON_ENGINE_ASSET_SOURCES})

add_library(aeon_engine_assets STATIC
    ${AEON_ENGINE_ASSET_SOURCES}
)

target_link_libraries(aeon_engine_assets
    aeon_engine_common
    aeon_engine_data
    aeon_engine_resources
    aeon_engine_gfx_core
    aeon_engine_scene_core
    aeon_engine_scene_components
    aeon_engine_codecs
    aeon_utility
    aeon_logger
)

target_include_directories(aeon_engine_assets
    PUBLIC include
)

set_target_properties(
    aeon_engine_assets PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    FOLDER engine
)

install(
    TARGETS aeon_engine_assets
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

install(
    DIRECTORY include/
    DESTINATION include
    FILES_MATCHING PATTERN "*.h"
)

