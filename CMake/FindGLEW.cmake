include(GenericFindScript)

generic_find_script(
    NAME GLEW
    HEADER GL/glew.h
    LIBRARY_WIN_DEBUG glew32d
    LIBRARY_WIN_RELEASE glew32
    LIBRARY GLEW
)
