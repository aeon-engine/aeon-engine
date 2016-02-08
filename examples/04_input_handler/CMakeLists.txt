include(Utility)

add_executable(example_04_input_handler main.cpp application.cpp application.h)

target_include_directories(example_04_input_handler
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(example_04_input_handler aeon_engine)

set_target_properties(
    example_04_input_handler PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    FOLDER examples
)

set_working_dir(example_04_input_handler "${CMAKE_SOURCE_DIR}/bin")
