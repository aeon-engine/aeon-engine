find_path (PNG_INCLUDE_DIRS "png.h"
    PATHS $ENV{PNG_ROOT}
    PATH_SUFFIXES include
)

if (PNG_INCLUDE_DIRS)
    set(PNG_FOUND "YES")

    get_filename_component(PNG_ROOT_DIR "${PNG_INCLUDE_DIRS}/../" ABSOLUTE)
    set(PNG_LIBRARY_DIR ${PNG_ROOT_DIR}/lib/)

    if (MSVC)
        find_library(PNG_LIBRARY_DEBUG "libpng16d" PATHS ${PNG_LIBRARY_DIR})
        find_library(PNG_LIBRARY_RELEASE "libpng16" PATHS ${PNG_LIBRARY_DIR})
    else ()
        find_library(PNG_LIBRARY_DEBUG "png" PATHS ${PNG_LIBRARY_DIR})
        find_library(PNG_LIBRARY_RELEASE "png" PATHS ${PNG_LIBRARY_DIR})
    endif ()

    if (NOT PNG_LIBRARY_DEBUG)
        message(FATAL_ERROR "PNG not found!")
    endif ()

    if (NOT PNG_LIBRARY_RELEASE)
        message(FATAL_ERROR "PNG not found!")
    endif ()

    set(PNG_LIBRARIES
        debug ${PNG_LIBRARY_DEBUG}
        optimized ${PNG_LIBRARY_RELEASE}
    )

    message (STATUS "Found PNG: ${PNG_ROOT_DIR}")
else ()
    message (FATAL_ERROR "PNG not found!")
endif ()
