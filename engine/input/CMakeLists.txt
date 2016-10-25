set (AEON_ENGINE_INPUT_SOURCES
    include/aeon/input/input_handler.h
    include/aeon/input/input_keyboard_keys.h
    include/aeon/input/input_listener.h
    include/aeon/input/input_mouse_buttons.h
    src/input_handler.cpp
)

source_group(input FILES ${AEON_ENGINE_INPUT_SOURCES})

add_library(aeon_engine_input STATIC
    ${AEON_ENGINE_INPUT_SOURCES}
)

target_link_libraries(aeon_engine_input
    aeon
)

target_include_directories(aeon_engine_input
    PUBLIC include
)

set_target_properties(
    aeon_engine_input PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    FOLDER engine
)
