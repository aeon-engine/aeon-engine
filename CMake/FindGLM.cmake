find_path (GLM_INCLUDE_DIRS "glm/glm.hpp"
    PATHS $ENV{GLM_ROOT}
    NO_DEFAULT_PATH
)

if (GLM_INCLUDE_DIRS)
    set(GLM_FOUND "YES")

    set(GLM_ROOT_DIR "${GLM_INCLUDE_DIRS}")
    message(STATUS "Found GLM: ${GLM_ROOT_DIR}")
else ()
    message(FATAL_ERROR "GLM not found!")
endif ()
