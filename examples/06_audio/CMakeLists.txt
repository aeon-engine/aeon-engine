include(Utility)

add_executable(example_06_audio main.cpp application.cpp application.h)

target_include_directories(example_06_audio
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(example_06_audio aeon_engine)

set_target_properties(
    example_06_audio PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    FOLDER examples
)

set_working_dir(example_06_audio "${CMAKE_SOURCE_DIR}/bin")
