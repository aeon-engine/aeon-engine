include (SelectLibraryConfigurations)
include (FindPackageHandleStandardArgs)

# The HINTS option should only be used for values computed from the system.
set (_GLM_HINTS
    $ENV{GLM_ROOT}
)
# Hard-coded guesses should still go in PATHS. This ensures that the user
# environment can always override hard guesses.
set (_GLM_PATHS
    $ENV{GLM_ROOT}
)

find_path (GLM_ROOT_DIR "glm.hpp"
    HINTS ${_GLM_HINTS}
    PATHS ${_GLM_PATHS}
    PATH_SUFFIXES
        glm
)

if (GLM_ROOT_DIR)
    set (GLM_FOUND "YES")

    get_filename_component(GLM_ROOT_DIR "${GLM_ROOT_DIR}/../" ABSOLUTE)
    set (GLM_INCLUDE_DIRS ${GLM_ROOT_DIR})

    message (STATUS "Found GLM: ${GLM_ROOT_DIR}")
else ()
    message (FATAL_ERROR "GLM not found!")
endif ()

