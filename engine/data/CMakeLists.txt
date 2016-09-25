set (AEON_ENGINE_DATA_SOURCES
    include/aeon/data/atlas.h
    include/aeon/data/image.h
    include/aeon/data/material.h
    include/aeon/data/mesh.h
    include/aeon/data/shader.h
    src/atlas.cpp
    src/image.cpp
    src/material.cpp
    src/shader.cpp
)

source_group(data FILES ${AEON_ENGINE_DATA_SOURCES})

add_library(aeon_engine_data STATIC
    ${AEON_ENGINE_DATA_SOURCES}
)

target_link_libraries(aeon_engine_data
    aeon_engine_common
    aeon
    glm
)

target_include_directories(aeon_engine_data
    PUBLIC include
    PRIVATE ${CMAKE_BINARY_DIR}
)

