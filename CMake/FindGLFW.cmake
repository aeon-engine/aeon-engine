include(GenericFindScript)

generic_find_script(
    NAME GLFW
    HEADER GLFW/glfw3.h
    LIBRARY_WIN_DEBUG glfw3d
    LIBRARY_WIN_RELEASE glfw3
    LIBRARY glfw3
)
