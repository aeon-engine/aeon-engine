include(Utility)

add_executable(example_06_mesh_loading main.cpp application.cpp application.h)

target_include_directories(example_06_mesh_loading
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(example_06_mesh_loading aeon_engine)

set_target_properties(
    example_06_mesh_loading PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    FOLDER examples
)

set_working_dir(example_06_mesh_loading "${CMAKE_SOURCE_DIR}/bin")

install(
    TARGETS example_06_mesh_loading
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)
