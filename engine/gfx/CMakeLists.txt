add_subdirectory(core)

if (AEON_GFX_GL)
    add_subdirectory(gl_common)
    add_subdirectory(gl)
endif ()

if (AEON_GFX_GLES2)
    add_subdirectory(gl_common)
    add_subdirectory(gles2)
endif ()
