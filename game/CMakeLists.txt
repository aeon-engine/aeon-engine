include(Common)

################################################################################

add_source_path(AEON_APPLICATION_SOURCES common)

################################################################################

generate_source_groups("${AEON_APPLICATION_SOURCES}")

add_executable(aeon_game ${AEON_APPLICATION_SOURCES})

target_include_directories(aeon_game
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(aeon_game aeon_engine)

set_target_properties(
    aeon_game PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    FOLDER game
)
