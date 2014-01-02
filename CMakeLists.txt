project(AEON)
cmake_minimum_required(VERSION 2.8)

set(AEON_VERSION_MAJOR "0")
set(AEON_VERSION_MINOR "1")
set(AEON_VERSION_PATCH "0")

set(AEON_VERSION "${AEON_VERSION_MAJOR}.${AEON_VERSION_MINOR}.${AEON_VERSION_PATCH}")

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
option(AEON_CONSOLE_OUTPUT_DEBUG_MSGS "Output extra debug logging" OFF)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMake/modules)

find_package(OpenGL REQUIRED)
find_package(GLFW3)
find_package(GLEW REQUIRED)

if (UNIX)
	set(CMAKE_CXX_FLAGS "-c -Wall -Wfatal-errors -std=c++11 -O2")
endif (UNIX)

if (BUILD_SHARED_LIBS)
    set(_AEON_BUILD_DLL 1)
endif ()

add_subdirectory(src)

