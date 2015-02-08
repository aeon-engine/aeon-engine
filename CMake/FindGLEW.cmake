include (SelectLibraryConfigurations)
include (FindPackageHandleStandardArgs)

# The HINTS option should only be used for values computed from the system.
set (_GLEW_HINTS
    $ENV{GLEW_ROOT}
)
# Hard-coded guesses should still go in PATHS. This ensures that the user
# environment can always override hard guesses.
set (_GLEW_PATHS
    $ENV{GLEW_ROOT}
)

find_path (GLEW_ROOT_DIR "glew.h"
    HINTS ${_GLEW_HINTS}
    PATHS ${_GLEW_PATHS}
    PATH_SUFFIXES
        include/GL
)

if (GLEW_ROOT_DIR)
    set (GLEW_FOUND "YES")

    get_filename_component(GLEW_ROOT_DIR "${GLEW_ROOT_DIR}/../../" ABSOLUTE)
    set (GLEW_INCLUDE_DIRS ${GLEW_ROOT_DIR}/include)

    set (GLEW_LIBRARY_DIR ${GLEW_ROOT_DIR}/lib/)
    find_library(GLEW_LIBRARY "glew" HINTS ${GLEW_LIBRARY_DIR})

    message (STATUS "Found GLEW: ${GLEW_ROOT_DIR}")
else ()
    message (FATAL_ERROR "GLEW not found!")
endif ()

