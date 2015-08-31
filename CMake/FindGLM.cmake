find_path(
    GLM_INCLUDE_DIRS "glm/glm.hpp"
    PATH_SUFFIXES include
)

if (GLM_INCLUDE_DIRS)
    set(GLM_FOUND "YES")

    set(GLM_ROOT_DIR "${GLM_INCLUDE_DIRS}")
    message(STATUS "Found GLM: ${GLM_ROOT_DIR}")
else ()
    message(FATAL_ERROR "GLM not found!")
endif ()
