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
    include/aeon/resources/resource_type.h
    include/aeon/resources/shader.h
    include/aeon/resources/submesh.h
    src/atlas.cpp
    src/codecs
    src/image.cpp
    src/material.cpp
    src/mesh.cpp
    src/mesh_node.cpp
    src/resource_manager.cpp
    src/shader.cpp
)

source_group(resources FILES ${AEON_ENGINE_RESOURCES_SOURCES})

set (AEON_ENGINE_RESOURCE_PROVIDER_SOURCES
    include/aeon/resources/providers/filesystem_provider.h
    include/aeon/resources/providers/resourcefile_provider.h
    include/aeon/resources/providers/resource_provider.h
    src/providers/filesystem_provider.cpp
    src/providers/resourcefile_provider.cpp
)

source_group(resources\\providers FILES ${AEON_ENGINE_RESOURCE_PROVIDER_SOURCES})

set (AEON_ENGINE_RESOURCE_WRAPPER_SOURCES
    include/aeon/resources/wrappers/atlas_resource_wrapper.h
    include/aeon/resources/wrappers/image_resource_wrapper.h
    include/aeon/resources/wrappers/material_resource_wrapper.h
    include/aeon/resources/wrappers/mesh_resource_wrapper.h
    include/aeon/resources/wrappers/resource_wrapper.h
    include/aeon/resources/wrappers/shader_resource_wrapper.h
    src/wrappers/atlas_resource_wrapper.cpp
    src/wrappers/image_resource_wrapper.cpp
    src/wrappers/material_resource_wrapper.cpp
    src/wrappers/mesh_resource_wrapper.cpp
    src/wrappers/resource_wrapper.cpp
    src/wrappers/shader_resource_wrapper.cpp
)

source_group(resources\\wrappers FILES ${AEON_ENGINE_RESOURCE_WRAPPER_SOURCES})

set (AEON_ENGINE_RESOURCE_CODEC_SOURCES
    include/aeon/resources/codecs/atlas_codec.h
    include/aeon/resources/codecs/codec.h
    include/aeon/resources/codecs/codec_manager.h
    include/aeon/resources/codecs/image_codec.h
    include/aeon/resources/codecs/image_png_codec.h
    include/aeon/resources/codecs/material_codec.h
    include/aeon/resources/codecs/mesh_assimp_codec.h
    include/aeon/resources/codecs/mesh_codec.h
    include/aeon/resources/codecs/shader_codec.h
    src/codecs/atlas_codec.cpp
    src/codecs/codec_manager.cpp
    src/codecs/image_png_codec.cpp
    src/codecs/material_codec.cpp
    src/codecs/mesh_assimp_codec.cpp
    src/codecs/shader_codec.cpp
)

source_group(resources\\codecs FILES ${AEON_ENGINE_RESOURCE_CODEC_SOURCES})

add_library(aeon_engine_resources STATIC
    ${AEON_ENGINE_RESOURCES_SOURCES}
    ${AEON_ENGINE_RESOURCE_PROVIDER_SOURCES}
    ${AEON_ENGINE_RESOURCE_WRAPPER_SOURCES}
    ${AEON_ENGINE_RESOURCE_CODEC_SOURCES}
)

target_link_libraries(aeon_engine_resources
    aeon_engine_common
    aeon_engine_data
    aeon_engine_platform
    aeon
    glm
    assimp
    png_static
    freetype
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

