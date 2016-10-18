include(Utility)

add_executable(example_07_editor main.cpp application.cpp application.h)

target_include_directories(example_07_editor
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(example_07_editor aeon_engine)

set_target_properties(
    example_07_editor PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    FOLDER examples
)

set_working_dir(example_07_editor "${CMAKE_SOURCE_DIR}/bin")
