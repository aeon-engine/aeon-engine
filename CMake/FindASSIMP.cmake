include(GenericFindScript)

generic_find_script(
    NAME ASSIMP
    HEADER assimp/scene.h
    LIBRARY_WIN_DEBUG assimpd
    LIBRARY_WIN_RELEASE assimp
    LIBRARY assimp
)
