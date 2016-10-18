set (AEON_ENGINE_GFX_GL_SOURCES
    include/aeon/gfx/gl/gfx_gl_buffer.h
    include/aeon/gfx/gl/gfx_gl_buffer_manager.h
    include/aeon/gfx/gl/gfx_gl_device.h
    include/aeon/gfx/gl/gfx_gl_imgui_renderer.h
    include/aeon/gfx/gl/gfx_gl_material.h
    include/aeon/gfx/gl/gfx_gl_material_manager.h
    include/aeon/gfx/gl/gfx_gl_mesh.h
    include/aeon/gfx/gl/gfx_gl_monitor.h
    include/aeon/gfx/gl/gfx_gl_shader.h
    include/aeon/gfx/gl/gfx_gl_shader_manager.h
    include/aeon/gfx/gl/gfx_gl_texture.h
    include/aeon/gfx/gl/gfx_gl_texture_manager.h
    include/aeon/gfx/gl/gfx_gl_vertex_array_object.h
    include/aeon/gfx/gl/gfx_gl_window.h
    src/gfx_gl_buffer.cpp
    src/gfx_gl_buffer_manager.cpp
    src/gfx_gl_device.cpp
    src/gfx_gl_imgui_renderer.cpp
    src/gfx_gl_material.cpp
    src/gfx_gl_material_manager.cpp
    src/gfx_gl_mesh.cpp
    src/gfx_gl_monitor.cpp
    src/gfx_gl_shader.cpp
    src/gfx_gl_shader_manager.cpp
    src/gfx_gl_texture.cpp
    src/gfx_gl_texture_manager.cpp
    src/gfx_gl_vertex_array_object.cpp
    src/gfx_gl_window.cpp
)

source_group(gfx\\gl FILES ${AEON_ENGINE_GFX_GL_SOURCES})

add_library(aeon_engine_gfx_gl STATIC
    ${AEON_ENGINE_GFX_GL_SOURCES}
)

target_link_libraries(aeon_engine_gfx_gl
    aeon_engine_gfx_core
    aeon_engine_gfx_gl_common
    aeon_engine_input
    glew_s
    glfw
    aeon
    glm
)

target_include_directories(aeon_engine_gfx_gl
    PUBLIC include
    PRIVATE ${CMAKE_BINARY_DIR}
)

set_target_properties(
    aeon_engine_gfx_gl PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    FOLDER engine
)
