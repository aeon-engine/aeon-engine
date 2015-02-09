include (SelectLibraryConfigurations)
include (FindPackageHandleStandardArgs)

# The HINTS option should only be used for values computed from the system.
set (_ASSIMP_HINTS
    $ENV{ASSIMP_ROOT}
)
# Hard-coded guesses should still go in PATHS. This ensures that the user
# environment can always override hard guesses.
set (_ASSIMP_PATHS
    $ENV{ASSIMP_ROOT}
)

find_path (ASSIMP_ROOT_DIR "scene.h"
    HINTS ${_ASSIMP_HINTS}
    PATHS ${_ASSIMP_PATHS}
    PATH_SUFFIXES
        include/assimp
)

if (ASSIMP_ROOT_DIR)
    set (ASSIMP_FOUND "YES")

    get_filename_component(ASSIMP_ROOT_DIR "${ASSIMP_ROOT_DIR}/../../" ABSOLUTE)
    set (ASSIMP_INCLUDE_DIRS ${ASSIMP_ROOT_DIR}/include)

    set (ASSIMP_LIBRARY_DIR ${ASSIMP_ROOT_DIR}/lib/)

    if (MSVC)
        find_library(ASSIMP_LIBRARY_DEBUG "assimpd" HINTS ${ASSIMP_LIBRARY_DIR})
        find_library(ASSIMP_LIBRARY_RELEASE "assimp" HINTS ${ASSIMP_LIBRARY_DIR})
    else ()
        find_library(ASSIMP_LIBRARY_DEBUG "assimp" HINTS ${ASSIMP_LIBRARY_DIR})
        find_library(ASSIMP_LIBRARY_RELEASE "assimp" HINTS ${ASSIMP_LIBRARY_DIR})
    endif ()

    message (STATUS "Found Open Asset Import Library: ${ASSIMP_ROOT_DIR}")
else ()
    message (FATAL_ERROR "Open Asset Import Library not found!")
endif ()

