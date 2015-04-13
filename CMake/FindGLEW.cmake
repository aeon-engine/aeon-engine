find_path(GLEW_INCLUDE_DIRS "GL/glew.h"
    PATHS $ENV{GLEW_ROOT}
    PATH_SUFFIXES include
    NO_DEFAULT_PATH
)

if (GLEW_INCLUDE_DIRS)
    set(GLEW_FOUND "YES")

    get_filename_component(GLEW_ROOT_DIR "${GLEW_INCLUDE_DIRS}/../" ABSOLUTE)
    set(GLEW_LIBRARY_DIR ${GLEW_ROOT_DIR}/lib/)

    if (MSVC)
        find_library(GLEW_LIBRARY_DEBUG "glew32d" PATHS ${GLEW_LIBRARY_DIR} NO_DEFAULT_PATH)
        find_library(GLEW_LIBRARY_RELEASE "glew32" PATHS ${GLEW_LIBRARY_DIR} NO_DEFAULT_PATH)
    else ()
        find_library(GLEW_LIBRARY_DEBUG "glew" PATHS ${GLEW_LIBRARY_DIR} NO_DEFAULT_PATH)
        find_library(GLEW_LIBRARY_RELEASE "glew" PATHS ${GLEW_LIBRARY_DIR} NO_DEFAULT_PATH)
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

    message("${GLEW_LIBRARIES}")

    message(STATUS "Found GLEW: ${GLEW_ROOT_DIR}")
else ()
    message(FATAL_ERROR "GLEW not found!")
endif ()
