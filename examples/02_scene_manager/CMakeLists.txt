include(Utility)

add_executable(example_02_scene_manager main.cpp application.cpp application.h)

target_include_directories(example_02_scene_manager
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(example_02_scene_manager aeon_engine)

set_target_properties(
    example_02_scene_manager PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    FOLDER examples
)

set_working_dir(example_02_scene_manager "${CMAKE_SOURCE_DIR}/bin")
