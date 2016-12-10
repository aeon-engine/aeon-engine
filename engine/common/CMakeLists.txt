set (AEON_ENGINE_COMMON_SOURCES
    include/aeon/common/cached_object.h
    include/aeon/common/exception.h
    include/aeon/common/has_z_order.h
    include/aeon/common/logger.h
    include/aeon/common/object_cache.h
    src/logger.cpp
)

source_group(common FILES ${AEON_ENGINE_COMMON_SOURCES})

set (AEON_ENGINE_COMMON_TYPES_SOURCES
    include/aeon/common/types/color.h
    include/aeon/common/types/rectangle.h
    src/types/color.cpp
)

source_group(common\\types FILES ${AEON_ENGINE_COMMON_TYPES_SOURCES})

add_library(aeon_engine_common STATIC
    ${AEON_ENGINE_COMMON_SOURCES}
    ${AEON_ENGINE_COMMON_TYPES_SOURCES}
)

target_link_libraries(aeon_engine_common
    aeon
    glm
)

target_include_directories(aeon_engine_common
    PUBLIC include
    PRIVATE ${CMAKE_BINARY_DIR}
)

set_target_properties(
    aeon_engine_common PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    FOLDER engine
)

install(
    TARGETS aeon_engine_common
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

install(
    DIRECTORY include/
    DESTINATION include
    FILES_MATCHING PATTERN "*.h"
)

