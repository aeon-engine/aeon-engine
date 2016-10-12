set (AEON_ENGINE_ASSET_SOURCES
    include/aeon/assets/asset_manager.h
    src/asset_manager.cpp
)

source_group(gfx\\assets FILES ${AEON_ENGINE_ASSET_SOURCES})

add_library(aeon_engine_assets STATIC
    ${AEON_ENGINE_ASSET_SOURCES}
)

target_link_libraries(aeon_engine_assets
    aeon_engine_common
    aeon_engine_data
    aeon_engine_resources
    aeon_engine_gfx_core
    aeon_engine_scene_core
    aeon
)

target_include_directories(aeon_engine_assets
    PUBLIC include
)

set_target_properties(
    aeon_engine_assets PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    FOLDER engine
)
