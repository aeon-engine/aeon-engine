set (AEON_ENGINE_STORAGE_SOURCES
    include/aeon/storage/resource_file.h
    src/resource_file.cpp
)

source_group(storage FILES ${AEON_ENGINE_STORAGE_SOURCES})

add_library(aeon_engine_storage STATIC
    ${AEON_ENGINE_STORAGE_SOURCES}
)

target_link_libraries(aeon_engine_storage
    aeon_engine_platform
    aeon
)

target_include_directories(aeon_engine_storage
    PUBLIC include
)

set_target_properties(
    aeon_engine_storage PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    FOLDER engine
)

install(
    TARGETS aeon_engine_storage
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

install(
    DIRECTORY include/
    DESTINATION include
    FILES_MATCHING PATTERN "*.h"
)

