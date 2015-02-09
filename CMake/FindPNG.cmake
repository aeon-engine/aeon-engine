include (SelectLibraryConfigurations)
include (FindPackageHandleStandardArgs)

# The HINTS option should only be used for values computed from the system.
set (_PNG_HINTS
    $ENV{PNG_ROOT}
)
# Hard-coded guesses should still go in PATHS. This ensures that the user
# environment can always override hard guesses.
set (_PNG_PATHS
    $ENV{PNG_ROOT}
)

find_path (PNG_ROOT_DIR "png.h"
    HINTS ${_PNG_HINTS}
    PATHS ${_PNG_PATHS}
    PATH_SUFFIXES
        include
)

if (PNG_ROOT_DIR)
    set (PNG_FOUND "YES")

    get_filename_component(PNG_ROOT_DIR "${PNG_ROOT_DIR}/../" ABSOLUTE)
    set (PNG_INCLUDE_DIRS ${PNG_ROOT_DIR}/include)

    set (PNG_LIBRARY_DIR ${PNG_ROOT_DIR}/lib/)

    if (MSVC)
        find_library(PNG_LIBRARY_DEBUG "libpng16d" HINTS ${PNG_LIBRARY_DIR})
        find_library(PNG_LIBRARY_RELEASE "libpng16" HINTS ${PNG_LIBRARY_DIR})
    else ()
        find_library(PNG_LIBRARY_DEBUG "png" HINTS ${PNG_LIBRARY_DIR})
        find_library(PNG_LIBRARY_RELEASE "png" HINTS ${PNG_LIBRARY_DIR})
    endif ()

    message (STATUS "Found PNG: ${PNG_ROOT_DIR}")
else ()
    message (FATAL_ERROR "PNG not found!")
endif ()

