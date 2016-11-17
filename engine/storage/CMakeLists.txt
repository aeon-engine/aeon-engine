set (AEON_ENGINE_STORAGE_SOURCES
    include/aeon/storage/resource_file.h
    include/aeon/storage/resource_file_structs.h
    include/aeon/storage/resource_file_chunk.h
    include/aeon/storage/resource_file_directory.h
    src/resource_file.cpp
    src/resource_file_chunk.cpp
    src/resource_file_directory.cpp
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
