find_path (GLM_INCLUDE_DIRS "glm.hpp"
    PATHS $ENV{GLM_ROOT}
    PATH_SUFFIXES glm
)

if (GLM_INCLUDE_DIRS)
    set(GLM_FOUND "YES")

    get_filename_component(GLM_ROOT_DIR "${GLM_INCLUDE_DIRS}/../" ABSOLUTE)
    message(STATUS "Found GLM: ${GLM_ROOT_DIR}")
else ()
    message(FATAL_ERROR "GLM not found!")
endif ()

