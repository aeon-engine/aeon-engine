set (AEON_ENGINE_GFX_CORE_SOURCES
    include/aeon/gfx/gfx_atlas.h
    include/aeon/gfx/gfx_atlas_manager.h
    include/aeon/gfx/gfx_buffer.h
    include/aeon/gfx/gfx_buffer_manager.h
    include/aeon/gfx/gfx_camera.h
    include/aeon/gfx/gfx_device.h
    include/aeon/gfx/gfx_exception.h
    include/aeon/gfx/gfx_frame_listener.h
    include/aeon/gfx/gfx_imgui_listener.h
    include/aeon/gfx/gfx_imgui_renderer.h
    include/aeon/gfx/gfx_material.h
    include/aeon/gfx/gfx_material_manager.h
    include/aeon/gfx/gfx_mesh.h
    include/aeon/gfx/gfx_monitor.h
    include/aeon/gfx/gfx_render_target.h
    include/aeon/gfx/gfx_shader.h
    include/aeon/gfx/gfx_shader_manager.h
    include/aeon/gfx/gfx_texture.h
    include/aeon/gfx/gfx_texture_manager.h
    include/aeon/gfx/gfx_viewport.h
    include/aeon/gfx/gfx_window.h
    include/aeon/gfx/gfx_window_settings.h
    src/gfx_atlas.cpp
    src/gfx_atlas_manager.cpp
    src/gfx_buffer.cpp
    src/gfx_buffer_manager.cpp
    src/gfx_camera.cpp
    src/gfx_device.cpp
    src/gfx_render_target.cpp
    src/gfx_shader.cpp
    src/gfx_viewport.cpp
)

source_group(gfx\\core FILES ${AEON_ENGINE_GFX_CORE_SOURCES})

add_library(aeon_engine_gfx_core STATIC
    ${AEON_ENGINE_GFX_CORE_SOURCES}
)

target_link_libraries(aeon_engine_gfx_core
    aeon_engine_common
    aeon_engine_data
    aeon_engine_resources
    aeon
    glm
    imgui
)

target_include_directories(aeon_engine_gfx_core
    PUBLIC include
)

set_target_properties(
    aeon_engine_gfx_core PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    FOLDER engine
)
