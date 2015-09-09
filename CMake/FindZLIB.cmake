include(GenericFindScript)

generic_find_script(
    NAME ZLIB
    HEADER zlib.h
    LIBRARY_WIN_DEBUG zlibd
    LIBRARY_WIN_RELEASE zlib
    LIBRARY z
)
