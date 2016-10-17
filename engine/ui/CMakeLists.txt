set (AEON_ENGINE_UI_SOURCES
    include/aeon/ui/ui_manager.h
    src/ui_manager.cpp
)

source_group(ui FILES ${AEON_ENGINE_UI_SOURCES})

add_library(aeon_engine_ui STATIC
    ${AEON_ENGINE_UI_SOURCES}
)

target_link_libraries(aeon_engine_ui
    aeon_engine_gfx_core
    aeon
    imgui
)

target_include_directories(aeon_engine_ui
    PUBLIC include
)

set_target_properties(
    aeon_engine_ui PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    FOLDER engine
)
