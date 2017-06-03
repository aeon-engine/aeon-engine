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

set (AEON_ENGINE_SCENE_CORE_SOURCES
    include/aeon/scene/camera.h
    include/aeon/scene/exceptions.h
    include/aeon/scene/render_layer.h
    include/aeon/scene/render_queue.h
    include/aeon/scene/scene_manager.h
    include/aeon/scene/scene_node.h
    include/aeon/scene/movable_object.h
    include/aeon/scene/component.h
    src/camera.cpp
    src/render_queue.cpp
    src/scene_manager.cpp
    src/scene_node.cpp
    src/movable_object.cpp
    src/component.cpp
)

source_group(scene\\core FILES ${AEON_ENGINE_SCENE_CORE_SOURCES})

add_library(aeon_engine_scene_core STATIC
    ${AEON_ENGINE_SCENE_CORE_SOURCES}
)

target_link_libraries(aeon_engine_scene_core
    aeon_engine_common
    aeon_engine_gfx_core
    aeon_common
)

target_include_directories(aeon_engine_scene_core
    PUBLIC include
)

set_target_properties(
    aeon_engine_scene_core PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    FOLDER engine/scene
)

install(
    TARGETS aeon_engine_scene_core
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

install(
    DIRECTORY include/
    DESTINATION include
    FILES_MATCHING PATTERN "*.h"
)

