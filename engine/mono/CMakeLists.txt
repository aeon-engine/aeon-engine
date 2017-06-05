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

include(Mono)

if (MSVC)
    include_external_msproject(
        AeonEngineMono
        ${CMAKE_CURRENT_SOURCE_DIR}/managed/AeonEngineMono.csproj
        TYPE FAE04EC0-301F-11D3-BF4B-00C04F79EFBC
    )
else ()
    add_mono_assembly(
        TARGET AeonEngineMono
        DESTINATION ${CMAKE_BINARY_DIR}/bin
        TYPE library
        SOURCES
            managed/Color.cs
            managed/Object.cs
            managed/ResourceManager.cs
            managed/Sprite.cs
            managed/Vector2f.cs
    )
endif ()

###############################################################################

set (AEON_ENGINE_MONO_SOURCES
    include/aeon/mono/mono_exception.h
    include/aeon/mono/mono_application.h
    src/mono_application.cpp
    include/aeon/mono/mono_jit_manager.h
    src/mono_jit_manager.cpp
)

source_group(mono FILES ${AEON_ENGINE_MONO_SOURCES})

###############################################################################

set (AEON_ENGINE_MONO_MANAGED_INFERFACE_SOURCES
    src/managed_interface/mono_object_wrapper.h
)

source_group(mono\\managed_interface FILES ${AEON_ENGINE_MONO_MANAGED_INFERFACE_SOURCES})

###############################################################################


set (AEON_ENGINE_MONO_MANAGED_INTERFACE_CORE_SOURCES
    src/managed_interface/core/object.cpp
    src/managed_interface/core/object.h
    src/managed_interface/core/types.h
)

source_group(mono\\managed_interface\\core FILES ${AEON_ENGINE_MONO_MANAGED_INTERFACE_CORE_SOURCES})

###############################################################################

set (AEON_ENGINE_MONO_MANAGED_INTERFACE_ASSETS_SOURCES
    src/managed_interface/assets/atlas.cpp
    src/managed_interface/assets/atlas.h
    src/managed_interface/assets/material.cpp
    src/managed_interface/assets/material.h
)

source_group(mono\\managed_interface\\assets FILES ${AEON_ENGINE_MONO_MANAGED_INTERFACE_ASSETS_SOURCES})

###############################################################################

set (AEON_ENGINE_MONO_MANAGED_INTERFACE_RESOURCES_SOURCES
    src/managed_interface/resources/filesystem_collection_provider.cpp
    src/managed_interface/resources/filesystem_collection_provider.h
    src/managed_interface/resources/resource_manager.cpp
    src/managed_interface/resources/resource_manager.h
)

source_group(mono\\managed_interface\\resources FILES ${AEON_ENGINE_MONO_MANAGED_INTERFACE_RESOURCES_SOURCES})

###############################################################################

set (AEON_ENGINE_MONO_MANAGED_INTERFACE_SCENE_SOURCES
    src/managed_interface/scene/camera.cpp
    src/managed_interface/scene/camera.h
    src/managed_interface/scene/component.cpp
    src/managed_interface/scene/component.h
    src/managed_interface/scene/orthographic_camera.cpp
    src/managed_interface/scene/orthographic_camera.h
    src/managed_interface/scene/perspective_camera.cpp
    src/managed_interface/scene/perspective_camera.h
    src/managed_interface/scene/sprite.cpp
    src/managed_interface/scene/sprite.h
    src/managed_interface/scene/scene_node.cpp
    src/managed_interface/scene/scene_node.h
    src/managed_interface/scene/scene_manager.cpp
    src/managed_interface/scene/scene_manager.h
)

source_group(mono\\managed_interface\\scene FILES ${AEON_ENGINE_MONO_MANAGED_INTERFACE_SCENE_SOURCES})

###############################################################################

set (AEON_ENGINE_MONO_MANAGED_INTERFACE_GFX_SOURCES
    src/managed_interface/gfx/viewport.cpp
    src/managed_interface/gfx/viewport.h
)

source_group(mono\\managed_interface\\gfx FILES ${AEON_ENGINE_MONO_MANAGED_INTERFACE_GFX_SOURCES})

###############################################################################

add_library(aeon_engine_mono STATIC
    ${AEON_ENGINE_MONO_SOURCES}
    ${AEON_ENGINE_MONO_MANAGED_INFERFACE_SOURCES}
    ${AEON_ENGINE_MONO_MANAGED_INTERFACE_CORE_SOURCES}
    ${AEON_ENGINE_MONO_MANAGED_INTERFACE_ASSETS_SOURCES}
    ${AEON_ENGINE_MONO_MANAGED_INTERFACE_RESOURCES_SOURCES}
    ${AEON_ENGINE_MONO_MANAGED_INTERFACE_SCENE_SOURCES}
    ${AEON_ENGINE_MONO_MANAGED_INTERFACE_GFX_SOURCES}
)

target_link_libraries(aeon_engine_mono
    aeon_engine_application
    aeon_engine_common
    aeon_engine_resources
    aeon_common
    aeon_logger
    aeon_mono
)

target_include_directories(aeon_engine_mono
    PUBLIC include
    PRIVATE src
)

set_target_properties(
    aeon_engine_mono PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    FOLDER engine
)

install(
    TARGETS aeon_engine_mono
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

install(
    DIRECTORY include/
    DESTINATION include
    FILES_MATCHING PATTERN "*.h"
)
