find_path(
    GLEW_INCLUDE_DIRS "GL/glew.h"
    PATH_SUFFIXES include
)

if (GLEW_INCLUDE_DIRS)
    set(GLEW_FOUND "YES")

    get_filename_component(GLEW_ROOT_DIR "${GLEW_INCLUDE_DIRS}/../" ABSOLUTE)
    set(GLEW_LIBRARY_DIR ${GLEW_ROOT_DIR}/lib/)

    if (MSVC)
        find_library(GLEW_LIBRARY_DEBUG "glew32d" PATHS ${GLEW_LIBRARY_DIR})
        find_library(GLEW_LIBRARY_RELEASE "glew32" PATHS ${GLEW_LIBRARY_DIR})
    else ()
        find_library(GLEW_LIBRARY_DEBUG "GLEW" PATHS ${GLEW_LIBRARY_DIR})
        find_library(GLEW_LIBRARY_RELEASE "GLEW" PATHS ${GLEW_LIBRARY_DIR})
    endif ()

    if (NOT GLEW_LIBRARY_DEBUG)
        message(FATAL_ERROR "GLEW not found!")
    endif ()

    if (NOT GLEW_LIBRARY_RELEASE)
        message(FATAL_ERROR "GLEW not found!")
    endif ()

    set(GLEW_LIBRARIES
        debug ${GLEW_LIBRARY_DEBUG}
        optimized ${GLEW_LIBRARY_RELEASE}
    )

    message(STATUS "Found GLEW: ${GLEW_ROOT_DIR}")
else ()
    message(FATAL_ERROR "GLEW not found!")
endif ()
