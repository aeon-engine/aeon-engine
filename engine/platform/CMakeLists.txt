set (AEON_ENGINE_PLATFORM_SOURCES
    include/aeon/platform/platform_exception.h
    include/aeon/platform/platform_file_interface.h
    include/aeon/platform/platform_file_open_mode.h
    include/aeon/platform/platform_filesystem_interface.h
    include/aeon/platform/platform_interface.h
)

source_group(platform FILES ${AEON_ENGINE_PLATFORM_SOURCES})

set (AEON_ENGINE_PLATFORM_GENERIC_SOURCES
    include/aeon/platform/generic/platform_generic_file_interface.h
    include/aeon/platform/generic/platform_generic_filesystem_interface.h
    src/generic/platform_generic_file_interface.cpp
    src/generic/platform_generic_filesystem_interface.cpp
)

source_group(platform\\generic FILES ${AEON_ENGINE_PLATFORM_GENERIC_SOURCES})

add_library(aeon_engine_platform STATIC
    ${AEON_ENGINE_PLATFORM_SOURCES}
    ${AEON_ENGINE_PLATFORM_GENERIC_SOURCES}
)

target_link_libraries(aeon_engine_platform
    aeon
    aeon_engine_common
)

target_include_directories(aeon_engine_platform
    PUBLIC include
)

set_target_properties(
    aeon_engine_platform PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    FOLDER engine
)
