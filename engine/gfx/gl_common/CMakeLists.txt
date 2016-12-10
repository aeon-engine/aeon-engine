set (AEON_ENGINE_GFX_GL_COMMON_SOURCES
    include/aeon/gfx/gl_common/check_gl_error.h
    src/check_gl_error.cpp
)

source_group(gfx\\core FILES ${AEON_ENGINE_GFX_GL_COMMON_SOURCES})

add_library(aeon_engine_gfx_gl_common STATIC
    ${AEON_ENGINE_GFX_GL_COMMON_SOURCES}
)

target_link_libraries(aeon_engine_gfx_gl_common
    aeon_engine_common
    aeon_engine_gfx_core
    aeon
    glew_s
)

target_include_directories(aeon_engine_gfx_gl_common
    PUBLIC include
    PRIVATE ${CMAKE_BINARY_DIR}
)

set_target_properties(
    aeon_engine_gfx_gl_common PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    FOLDER engine
)

install(
    TARGETS aeon_engine_gfx_gl_common
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

install(
    DIRECTORY include/
    DESTINATION include
    FILES_MATCHING PATTERN "*.h"
)

