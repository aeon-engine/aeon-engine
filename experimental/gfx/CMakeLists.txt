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

set(AEON_ENGINE_GFX_MAIN_SOURCES
    src/gfx.cpp
    include/aeon/gfx/gfx.h
    include/aeon/gfx/gfx_resource.h
    include/aeon/gfx/gfx_shader.h
    include/aeon/gfx/gfx_texture.h
)

source_group(experimental\\gfx FILES ${AEON_ENGINE_GFX_MAIN_SOURCES})

set(AEON_ENGINE_GFX_SOURCES
    ${AEON_ENGINE_GFX_MAIN_SOURCES}
)

add_library(aeon_engine_experimental_gfx STATIC
    ${AEON_ENGINE_GFX_SOURCES}
)

target_link_libraries(aeon_engine_experimental_gfx
    PRIVATE
        aeon_common
        aeon_math
        aeon_imaging
)

target_include_directories(aeon_engine_experimental_gfx
    PUBLIC include
    PRIVATE src
)

set_target_properties(
    aeon_engine_experimental_gfx PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    FOLDER experimental/gfx
)

install(
    TARGETS aeon_engine_experimental_gfx
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

install(
    DIRECTORY include/
    DESTINATION include
    FILES_MATCHING PATTERN "*.h"
)
