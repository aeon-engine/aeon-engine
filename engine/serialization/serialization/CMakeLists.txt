set (AEON_ENGINE_SERIALIZATION_SOURCES
    include/aeon/serialization/serialization.h
    src/serialization.cpp
)

source_group(serialization FILES ${AEON_ENGINE_SERIALIZATION_SOURCES})

add_library(aeon_engine_serialization STATIC
    ${AEON_ENGINE_SERIALIZATION_SOURCES}
)

target_link_libraries(aeon_engine_serialization
    aeon_engine_common
    aeon
    json11
)

target_include_directories(aeon_engine_serialization
    PUBLIC
        include
        ${CMAKE_BINARY_DIR}
)

set_target_properties(
    aeon_engine_serialization PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    FOLDER engine
)

install(
    TARGETS aeon_engine_serialization
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

install(
    DIRECTORY include/
    DESTINATION include
    FILES_MATCHING PATTERN "*.h"
)

add_dependencies(aeon_engine_serialization aeon_engine_serialization_generator_runner)
