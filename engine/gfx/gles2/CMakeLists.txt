set (AEON_ENGINE_GFX_GLES2_SOURCES
    include/aeon/gfx/gles2/gfx_gles2_buffer.h
    include/aeon/gfx/gles2/gfx_gles2_buffer_manager.h
    include/aeon/gfx/gles2/gfx_gles2_device.h
    include/aeon/gfx/gles2/gfx_gles2_material.h
    include/aeon/gfx/gles2/gfx_gles2_material_manager.h
    include/aeon/gfx/gles2/gfx_gles2_mesh.h
    include/aeon/gfx/gles2/gfx_gles2_shader.h
    include/aeon/gfx/gles2/gfx_gles2_shader_manager.h
    include/aeon/gfx/gles2/gfx_gles2_texture.h
    include/aeon/gfx/gles2/gfx_gles2_texture_manager.h
    src/gfx_gles2_buffer.cpp
    src/gfx_gles2_buffer_manager.cpp
    src/gfx_gles2_device.cpp
    src/gfx_gles2_material.cpp
    src/gfx_gles2_material_manager.cpp
    src/gfx_gles2_mesh.cpp
    src/gfx_gles2_shader.cpp
    src/gfx_gles2_shader_manager.cpp
    src/gfx_gles2_texture.cpp
    src/gfx_gles2_texture_manager.cpp
)

source_group(gfx\\gles2 FILES ${AEON_ENGINE_GFX_GLES2_SOURCES})

add_library(aeon_engine_gfx_gles2 STATIC
    ${AEON_ENGINE_GFX_GLES2_SOURCES}
)

target_link_libraries(aeon_engine_gfx_gles2
    aeon_engine_gfx_core
    aeon_engine_gfx_gl_common
    aeon
    glm
)

target_include_directories(aeon_engine_gfx_gles2
    PUBLIC include
    PRIVATE ${CMAKE_BINARY_DIR}
)

set_target_properties(
    aeon_engine_gfx_gles2 PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    FOLDER engine
)
