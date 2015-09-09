include(GenericFindScript)

generic_find_script(
    NAME PNG
    HEADER png.h
    LIBRARY_WIN_DEBUG libpng16d
    LIBRARY_WIN_RELEASE libpng16
    LIBRARY png
)
