find_path (ZLIB_INCLUDE_DIRS "zlib.h"
    PATH_SUFFIXES include
)

if (ZLIB_INCLUDE_DIRS)
    set(ZLIB_FOUND "YES")

    get_filename_component(ZLIB_ROOT_DIR "${ZLIB_INCLUDE_DIRS}/../" ABSOLUTE)
    set(ZLIB_LIBRARY_DIR ${ZLIB_ROOT_DIR}/lib/)

    if (MSVC)
        find_library(ZLIB_LIBRARY_DEBUG "zlibd" PATHS ${ZLIB_LIBRARY_DIR})
        find_library(ZLIB_LIBRARY_RELEASE "zlib" PATHS ${ZLIB_LIBRARY_DIR})
    else ()
        find_library(ZLIB_LIBRARY_DEBUG "z" PATHS ${ZLIB_LIBRARY_DIR})
        find_library(ZLIB_LIBRARY_RELEASE "z" PATHS ${ZLIB_LIBRARY_DIR})
    endif ()

    if (NOT ZLIB_LIBRARY_DEBUG)
        message(FATAL_ERROR "PNG not found!")
    endif ()

    if (NOT ZLIB_LIBRARY_RELEASE)
        message(FATAL_ERROR "PNG not found!")
    endif ()

    set(ZLIB_LIBRARIES
        debug ${ZLIB_LIBRARY_DEBUG}
        optimized ${ZLIB_LIBRARY_RELEASE}
    )

    message(STATUS "Found Zlib: ${ZLIB_ROOT_DIR}")
else ()
    message(FATAL_ERROR "Zlib not found!")
endif ()
