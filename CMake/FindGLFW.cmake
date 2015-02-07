include (SelectLibraryConfigurations)
include (FindPackageHandleStandardArgs)

# The HINTS option should only be used for values computed from the system.
set (_GLFW_HINTS
    $ENV{GLFW_ROOT}
)
# Hard-coded guesses should still go in PATHS. This ensures that the user
# environment can always override hard guesses.
set (_GLFW_PATHS
    $ENV{GLFW_ROOT}
)

find_path (GLFW_ROOT_DIR "glfw3.h"
    HINTS ${_GLFW_HINTS}
    PATHS ${_GLFW_PATHS}
    PATH_SUFFIXES
        include/GLFW
)

if (GLFW_ROOT_DIR)
    set (GLFW_FOUND "YES")

    get_filename_component(GLFW_ROOT_DIR "${GLFW_ROOT_DIR}/../../" ABSOLUTE)
    set (GLFW_INCLUDE_DIRS ${GLFW_ROOT_DIR}/include)

    set (GLFW_LIBRARY_DIR ${GLFW_ROOT_DIR}/lib/)
    find_library(GLFW_LIBRARY "glfw3" HINTS ${GLFW_LIBRARY_DIR})


    message (STATUS "Found GLFW: ${GLFW_ROOT_DIR}")
else ()
    message (FATAL_ERROR "GLFW not found!")
endif ()

