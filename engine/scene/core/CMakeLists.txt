set (AEON_ENGINE_SCENE_CORE_SOURCES
    include/aeon/scene/animated_sprite.h
    include/aeon/scene/camera.h
    include/aeon/scene/exceptions.h
    include/aeon/scene/mesh.h
    include/aeon/scene/orthographic_camera.h
    include/aeon/scene/perspective_camera.h
    include/aeon/scene/render_layer.h
    include/aeon/scene/render_queue.h
    include/aeon/scene/scene_manager.h
    include/aeon/scene/scene_node.h
    include/aeon/scene/scene_object.h
    include/aeon/scene/sprite.h
    include/aeon/scene/sprite_animation_settings.h
    src/animated_sprite.cpp
    src/camera.cpp
    src/mesh.cpp
    src/orthographic_camera.cpp
    src/perspective_camera.cpp
    src/render_queue.cpp
    src/scene_manager.cpp
    src/scene_node.cpp
    src/scene_object.cpp
    src/sprite.cpp
    src/sprite_animation_settings.cpp
)

source_group(scene\\core FILES ${AEON_ENGINE_SCENE_CORE_SOURCES})

add_library(aeon_engine_scene_core STATIC
    ${AEON_ENGINE_SCENE_CORE_SOURCES}
)

target_link_libraries(aeon_engine_scene_core
    aeon_engine_common
    aeon_engine_gfx_core
    aeon
)

target_include_directories(aeon_engine_scene_core
    PUBLIC include
)

set_target_properties(
    aeon_engine_scene_core PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    FOLDER engine
)

install(
    TARGETS aeon_engine_scene_core
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

install(
    DIRECTORY include/
    DESTINATION include
    FILES_MATCHING PATTERN "*.h"
)

