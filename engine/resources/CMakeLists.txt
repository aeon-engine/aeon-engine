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

set (AEON_ENGINE_RESOURCES_SOURCES
    include/aeon/resources/atlas.h
    include/aeon/resources/exceptions.h
    include/aeon/resources/image.h
    include/aeon/resources/material.h
    include/aeon/resources/mesh.h
    include/aeon/resources/mesh_node.h
    include/aeon/resources/resource.h
    include/aeon/resources/resource_encoding.h
    include/aeon/resources/resource_manager.h
    include/aeon/resources/shader.h
    include/aeon/resources/submesh.h
    include/aeon/resources/scene.h
    src/atlas.cpp
    src/image.cpp
    src/material.cpp
    src/mesh.cpp
    src/mesh_node.cpp
    src/resource_manager.cpp
    src/shader.cpp
    src/scene.cpp
)

source_group(resources FILES ${AEON_ENGINE_RESOURCES_SOURCES})

set (AEON_ENGINE_RESOURCE_PROVIDER_SOURCES
    include/aeon/resources/providers/resource_info.h
    include/aeon/resources/providers/resource_collection_provider.h
    include/aeon/resources/providers/resource_provider.h
    include/aeon/resources/providers/filesystem_collection_provider.h
    src/providers/filesystem_collection_provider.cpp
    include/aeon/resources/providers/filesystem_provider.h
    src/providers/filesystem_provider.cpp
    src/providers/resource_provider.cpp
)

source_group(resources\\providers FILES ${AEON_ENGINE_RESOURCE_PROVIDER_SOURCES})

add_library(aeon_engine_resources STATIC
    ${AEON_ENGINE_RESOURCES_SOURCES}
    ${AEON_ENGINE_RESOURCE_PROVIDER_SOURCES}
)

target_link_libraries(aeon_engine_resources
    aeon_engine_common
    aeon_engine_data
    aeon_engine_io
    aeon_engine_serialization
    aeon_common
    aeon_logger
    aeon_math
    aeon_utility
)

target_include_directories(aeon_engine_resources
    PUBLIC include
    PRIVATE
        src
        ${CMAKE_BINARY_DIR}
)

set_target_properties(
    aeon_engine_resources PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    FOLDER engine
)

install(
    TARGETS aeon_engine_resources
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

install(
    DIRECTORY include/
    DESTINATION include
    FILES_MATCHING PATTERN "*.h"
)
