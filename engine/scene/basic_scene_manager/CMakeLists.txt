set (AEON_ENGINE_BASIC_SCENE_MANAGER_SOURCES
    include/aeon/scene/basic_scene_manager/basic_scene_manager.h
    src/basic_scene_manager.cpp
)

source_group(scene\\basic_scene_manager FILES ${AEON_ENGINE_BASIC_SCENE_MANAGER_SOURCES})

add_library(aeon_engine_basic_scene_manager STATIC
    ${AEON_ENGINE_BASIC_SCENE_MANAGER_SOURCES}
)

target_link_libraries(aeon_engine_basic_scene_manager
    aeon_engine_scene_core
    aeon
)

target_include_directories(aeon_engine_basic_scene_manager
    PUBLIC include
)

set_target_properties(
    aeon_engine_basic_scene_manager PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    FOLDER engine
)

install(
    TARGETS aeon_engine_basic_scene_manager
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

install(
    DIRECTORY include/
    DESTINATION include
    FILES_MATCHING PATTERN "*.h"
)

