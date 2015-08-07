find_path(ASSIMP_INCLUDE_DIRS "assimp/scene.h"
    PATHS $ENV{ASSIMP_ROOT}
    PATH_SUFFIXES include
)

if (ASSIMP_INCLUDE_DIRS)
    set(ASSIMP_FOUND "YES")

    get_filename_component(ASSIMP_ROOT_DIR "${ASSIMP_INCLUDE_DIRS}/../" ABSOLUTE)
    set(ASSIMP_LIBRARY_DIR ${ASSIMP_ROOT_DIR}/lib/)

    if (MSVC)
        find_library(ASSIMP_LIBRARY_DEBUG "assimpd" PATHS ${ASSIMP_LIBRARY_DIR})
        find_library(ASSIMP_LIBRARY_RELEASE "assimp" PATHS ${ASSIMP_LIBRARY_DIR})
    else ()
        find_library(ASSIMP_LIBRARY_DEBUG "assimp" PATHS ${ASSIMP_LIBRARY_DIR})
        find_library(ASSIMP_LIBRARY_RELEASE "assimp" PATHS ${ASSIMP_LIBRARY_DIR})
    endif ()

    if (NOT ASSIMP_LIBRARY_DEBUG)
        message(FATAL_ERROR "Open Asset Import Library not found!")
    endif ()

    if (NOT ASSIMP_LIBRARY_RELEASE)
        message(FATAL_ERROR "Open Asset Import Library not found!")
    endif ()

    set(ASSIMP_LIBRARIES
        debug ${ASSIMP_LIBRARY_DEBUG}
        optimized ${ASSIMP_LIBRARY_RELEASE}
    )

    message(STATUS "Found Open Asset Import Library: ${ASSIMP_ROOT_DIR}")
else ()
    message(FATAL_ERROR "Open Asset Import Library not found!")
endif ()
