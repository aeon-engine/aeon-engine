add_subdirectory(googletest)
add_subdirectory(zlib)
add_subdirectory(png)

if (AEON_GFX_GL)
    add_subdirectory(glew)
endif ()

if (AEON_PLATFORM_GLFW)
    add_subdirectory(glfw)
endif ()

add_subdirectory(glm)
add_subdirectory(libaeon)