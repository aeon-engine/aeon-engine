include(Utility)

add_executable(example_03_sprite_animation main.cpp application.cpp application.h)

target_include_directories(example_03_sprite_animation
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(example_03_sprite_animation aeon_engine)

set_target_properties(
    example_03_sprite_animation PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    FOLDER examples
)

set_working_dir(example_03_sprite_animation "${CMAKE_SOURCE_DIR}/bin")
