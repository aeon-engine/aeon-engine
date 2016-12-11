include(Utility)

add_executable(example_05_multiple_viewports main.cpp application.cpp application.h)

target_include_directories(example_05_multiple_viewports
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(example_05_multiple_viewports aeon_engine)

set_target_properties(
    example_05_multiple_viewports PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    FOLDER examples
)

set_working_dir(example_05_multiple_viewports "${CMAKE_SOURCE_DIR}/bin")

install(
    TARGETS example_05_multiple_viewports
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)
