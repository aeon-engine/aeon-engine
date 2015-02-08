include (SelectLibraryConfigurations)
include (FindPackageHandleStandardArgs)

# The HINTS option should only be used for values computed from the system.
set (_ZLIB_HINTS
    $ENV{ZLIB_ROOT}
)
# Hard-coded guesses should still go in PATHS. This ensures that the user
# environment can always override hard guesses.
set (_ZLIB_PATHS
    $ENV{ZLIB_ROOT}
)

find_path (ZLIB_ROOT_DIR "zlib.h"
    HINTS ${_ZLIB_HINTS}
    PATHS ${_ZLIB_PATHS}
    PATH_SUFFIXES
        include
)

if (ZLIB_ROOT_DIR)
    set (ZLIB_FOUND "YES")

    get_filename_component(ZLIB_ROOT_DIR "${ZLIB_ROOT_DIR}/../" ABSOLUTE)
    set (ZLIB_INCLUDE_DIRS ${ZLIB_ROOT_DIR}/include)

    set (ZLIB_LIBRARY_DIR ${ZLIB_ROOT_DIR}/lib/)
    find_library(ZLIB_LIBRARY "z" HINTS ${ZLIB_LIBRARY_DIR})

    message (STATUS "Found Zlib: ${ZLIB_ROOT_DIR}")
else ()
    message (FATAL_ERROR "Zlib not found!")
endif ()

