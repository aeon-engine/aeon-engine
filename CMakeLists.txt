cmake_minimum_required(VERSION 3.1.0)
project(AeonEngine)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/dep/cmake/")
set(CMAKE_PREFIX_PATH "$ENV{AEON_LIBRARIES_PATH};${CMAKE_PREFIX_PATH}")

include(CompilerFlags)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_CONFIGURATION_TYPES Debug Release CACHE TYPE INTERNAL FORCE)

set(CMAKE_DEBUG_POSTFIX "_d")

################################################################################

include(CTest)
enable_testing()

################################################################################

# Code coverage did not work on Xcode due to linker errors (missing libprofile_rt?)
if (NOT CMAKE_GENERATOR STREQUAL Xcode)
    if (APPLE)
        option(AEON_ENABLE_CLANG_COVERAGE "Compile with code coverage enabled for GCOV on OSX." OFF)

        if (AEON_ENABLE_CLANG_COVERAGE)
            message("Compiling with code coverage enabled for GCOV on OSX.")
            message(" - fprofile-arcs")
            message(" - ftest-coverage")

            set(AEON_CLANG_COVERAGE_COMPILER_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${AEON_CLANG_COVERAGE_COMPILER_FLAGS}")
            set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${AEON_CLANG_COVERAGE_COMPILER_FLAGS}")
        endif ()
    endif ()
endif ()

################################################################################

if (APPLE)
    message(STATUS "Building on Apple. Finding Frameworks.")
    find_library(COCOA_LIBRARY Cocoa)
    find_library(IOKIT_LIBRARY IOKit)
    find_library(COREVIDEO_LIBRARY CoreVideo)
    mark_as_advanced(COCOA_LIBRARY IOKIT_LIBRARY COREVIDEO_LIBRARY)

    message(STATUS "Cocoa: ${COCOA_LIBRARY}")
    message(STATUS "IOKit: ${IOKIT_LIBRARY}")
    message(STATUS "CoreVideo: ${COREVIDEO_LIBRARY}")
endif ()

if (MSVC)
    # Iterator debugging can not be disabled when linking with the standard Qt binaries on Windows.
    option(AEON_ENABLE_MSVC_ITERATOR_DEBUGGING "Enable iterator debugging in Visual Studio" ON)
    if (NOT AEON_ENABLE_MSVC_ITERATOR_DEBUGGING)
        message (STATUS "Disabling iterator debugging (_HAS_ITERATOR_DEBUGGING=0).")
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /D _HAS_ITERATOR_DEBUGGING=0")
    endif ()

    set(_AEON_ENABLE_MSVC_DEFAULT ON)
    if (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
        set(_AEON_ENABLE_MSVC_DEFAULT OFF)
    endif ()

    option(AEON_ENABLE_MSVC_MP_BUILD "Use the /MP flag in Visual Studio to use multiple processes per cpp file." ${_AEON_ENABLE_MSVC_DEFAULT})
    if (AEON_ENABLE_MSVC_MP_BUILD)
        message (STATUS "Using Visual Studio /MP flag.")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /MP")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
    endif ()
endif ()

################################################################################
# GFX options
################################################################################
set(AEON_GFX_RENDERER_NAME_OPENGL3_3 "OpenGL3.3")
set(AEON_GFX_RENDERER_NAME_GLES2 "GLES2")
set(AEON_GFX_RENDERER_NAME_NULL "NULL")

set(AEON_GFX_GL OFF)
set(AEON_GFX_GLES2 OFF)
set(AEON_GFX_NULL OFF)

set(AEON_GFX_RENDERER ${AEON_GFX_RENDERER_NAME_OPENGL3_3} CACHE STRING "GFX Render backend")
set_property(CACHE AEON_GFX_RENDERER PROPERTY STRINGS ${AEON_GFX_RENDERER_NAME_OPENGL3_3} ${AEON_GFX_RENDERER_NAME_GLES2} ${AEON_GFX_RENDERER_NAME_NULL})

if (AEON_GFX_RENDERER STREQUAL AEON_GFX_RENDERER_NAME_OPENGL3_3)
    message(STATUS "Using OpenGL as graphics renderer.")

    find_package(OpenGL REQUIRED)

    set(AEON_GFX_GL ON)
elseif (AEON_GFX_RENDERER STREQUAL AEON_GFX_RENDERER_NAME_GLES2)
    message (STATUS "Using OpenGL ES 2.0 as graphics renderer.")

    set(AEON_GFX_GLES2 ON)
elseif (AEON_GFX_RENDERER STREQUAL AEON_GFX_RENDERER_NAME_NULL)
    message (STATUS "Using Null as graphics renderer.")
    message (WARNING "This renderer is for debugging/testing only.")

    set(AEON_GFX_NULL ON)
else ()
    message (FATAL_ERROR "No valid graphics renderer selected.")
endif ()

################################################################################
# Platform options
################################################################################
set(AEON_PLATFORM_NAME_GLFW "GLFW")

set(AEON_PLATFORM_GLFW OFF)

set(AEON_PLATFORM ${AEON_PLATFORM_NAME_GLFW} CACHE STRING "Platform backend")
set_property(CACHE AEON_PLATFORM PROPERTY STRINGS ${AEON_PLATFORM_NAME_GLFW})

if (AEON_PLATFORM STREQUAL AEON_PLATFORM_NAME_GLFW)
    message (STATUS "Using GLFW as platform.")
    set(AEON_PLATFORM_GLFW ON)
else ()
    message (FATAL_ERROR "No valid platform was selected.")
endif ()

################################################################################
# Audio options
################################################################################
option(AEON_AUDIO_USE_OPENAL "Build and use OpenAL" OFF)

################################################################################
# Debugging options
################################################################################

# Check and log all OpenGL 3 and GLES 2 errors. Warning: This is very slow,
# only use for debugging purposes.
option(AEON_ENABLE_GL_ERROR_CHECKS "Check and log all OpenGL 3 and GLES 2 errors." ON)

################################################################################

add_subdirectory(dep)
add_subdirectory(engine)
add_subdirectory(examples)
add_subdirectory(tests)
add_subdirectory(doxygen)

################################################################################

include(CopyToRuntimePath)

option(AEON_SKIP_COPY_ASSETS_TO_RUNTIME_PATH "Skip copying asset files in the bin folder to the executable folders." OFF)
if (NOT AEON_SKIP_COPY_ASSETS_TO_RUNTIME_PATH)
    copy_folder_to_runtime_path(
        PATH bin
    )
endif ()
