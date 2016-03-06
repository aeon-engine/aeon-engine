include(Utility)

    file(
        GLOB_RECURSE resource_files
            ${CMAKE_SOURCE_DIR}/bin/*
    )

    message(STATUS "Files: ${resource_files}")

add_executable(example_01_basic_sprite main.cpp application.cpp application.h ${resource_files})

set_target_properties(example_01_basic_sprite PROPERTIES RESOURCE "${resource_files}" )

target_include_directories(example_01_basic_sprite
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(example_01_basic_sprite aeon_engine)

set_target_properties(
    example_01_basic_sprite PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    FOLDER examples
)

set_working_dir(example_01_basic_sprite "${CMAKE_SOURCE_DIR}/bin")
