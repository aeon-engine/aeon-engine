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

set (AEON_ENGINE_BASIC_SCENE_MANAGER_SOURCES
    include/aeon/scene/basic_scene_manager/basic_scene_manager.h
    src/basic_scene_manager.cpp
)

source_group(scene\\basic_scene_manager FILES ${AEON_ENGINE_BASIC_SCENE_MANAGER_SOURCES})

add_library(aeon_engine_basic_scene_manager STATIC
    ${AEON_ENGINE_BASIC_SCENE_MANAGER_SOURCES}
)

target_link_libraries(aeon_engine_basic_scene_manager
    aeon_engine_scene_core
)

target_include_directories(aeon_engine_basic_scene_manager
    PUBLIC include
)

set_target_properties(
    aeon_engine_basic_scene_manager PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    FOLDER engine/scene
)

install(
    TARGETS aeon_engine_basic_scene_manager
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

install(
    DIRECTORY include/
    DESTINATION include
    FILES_MATCHING PATTERN "*.h"
)

