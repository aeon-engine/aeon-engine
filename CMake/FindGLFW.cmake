find_path (GLFW_INCLUDE_DIRS "GLFW/glfw3.h"
    PATHS $ENV{GLFW_ROOT}
    PATH_SUFFIXES include
)

if (GLFW_INCLUDE_DIRS)
    set(GLFW_FOUND "YES")

    get_filename_component(GLFW_ROOT_DIR "${GLFW_INCLUDE_DIRS}/../" ABSOLUTE)
    set(GLFW_LIBRARY_DIR ${GLFW_ROOT_DIR}/lib/)

    if (MSVC)
        find_library(GLFW_LIBRARY_DEBUG "glfw3d" PATHS ${GLFW_LIBRARY_DIR})
        find_library(GLFW_LIBRARY_RELEASE "glfw3" PATHS ${GLFW_LIBRARY_DIR})
    else ()
        find_library(GLFW_LIBRARY_DEBUG "glfw" "glfw3" PATHS ${GLFW_LIBRARY_DIR})
        find_library(GLFW_LIBRARY_RELEASE "glfw" "glfw3" PATHS ${GLFW_LIBRARY_DIR})
    endif ()

    if (NOT GLFW_LIBRARY_DEBUG)
        message(FATAL_ERROR "GLFW not found!")
    endif ()

    if (NOT GLFW_LIBRARY_RELEASE)
        message(FATAL_ERROR "GLFW not found!")
    endif ()

    set(GLFW_LIBRARIES
        debug ${GLFW_LIBRARY_DEBUG}
        optimized ${GLFW_LIBRARY_RELEASE}
    )

    message(STATUS "Found GLFW: ${GLFW_ROOT_DIR}")
else ()
    message(FATAL_ERROR "GLFW not found!")
endif ()
