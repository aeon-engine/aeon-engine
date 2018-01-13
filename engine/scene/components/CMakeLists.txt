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

set (AEON_ENGINE_SCENE_COMPONENTS_SOURCES
    include/aeon/scene/components/animated_sprite.h
    include/aeon/scene/components/mesh.h
    include/aeon/scene/components/orthographic_camera.h
    include/aeon/scene/components/perspective_camera.h
    include/aeon/scene/components/sprite.h
    include/aeon/scene/components/sprite_animation_settings.h
    src/animated_sprite.cpp
    src/mesh.cpp
    src/orthographic_camera.cpp
    src/perspective_camera.cpp
    src/sprite.cpp
    src/sprite_animation_settings.cpp
)

source_group(scene\\components FILES ${AEON_ENGINE_SCENE_COMPONENTS_SOURCES})

add_library(aeon_engine_scene_components STATIC
    ${AEON_ENGINE_SCENE_COMPONENTS_SOURCES}
)

target_link_libraries(aeon_engine_scene_components
    aeon_engine_scene_core
    aeon_engine_gfx_core
    aeon_common
)

target_include_directories(aeon_engine_scene_components
    PUBLIC include
)

set_target_properties(
    aeon_engine_scene_components PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    FOLDER engine/scene
)

install(
    TARGETS aeon_engine_scene_components
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

install(
    DIRECTORY include/
    DESTINATION include
    FILES_MATCHING PATTERN "*.h"
)
