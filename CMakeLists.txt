cmake_minimum_required(VERSION 3.1.0)
project(AeonEngine)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/dep/cmake/")
set(CMAKE_PREFIX_PATH "$ENV{AEON_LIBRARIES_PATH};${CMAKE_PREFIX_PATH}")

include(CompilerFlags)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_CONFIGURATION_TYPES Debug Release CACHE TYPE INTERNAL FORCE)

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

################################################################################
# GFX options
################################################################################
option(AEON_GFX_GL "Use OpenGL as graphics renderer." ON)
option(AEON_GFX_GLES2 "Use OpenGL ES 2 as graphics renderer." OFF)

################################################################################
# Platform options
################################################################################
option(AEON_PLATFORM_GLFW "Use GLFW as platform (creates the window and context)" ON)
option(AEON_PLATFORM_RPI "Use Raspberry Pi as platform (creates the window and context)" OFF)

################################################################################
# Debugging options
################################################################################

# Check and log all OpenGL 3 and GLES 2 errors. Warning: This is very slow,
# only use for debugging purposes.
option(AEON_ENABLE_GL_ERROR_CHECKS "Check and log all OpenGL 3 and GLES 2 errors." ON)

if (AEON_ENABLE_GL_ERROR_CHECKS)
    message (STATUS "Enabled OpenGL error checking.")
endif ()

################################################################################

if (AEON_GFX_GL)
    find_package(OpenGL REQUIRED)
endif ()

if (AEON_PLATFORM_RPI)
    find_package(RaspberryPiSDK COMPONENTS
        EGL
        GLESv2
        vcos
        vchiq_arm
        bcm_host
    )

    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -static-libgcc")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++")
    set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -static-libgcc -static-libstdc++")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -static-libgcc -static-libstdc++")
endif ()

################################################################################

set(AEON_HAS_GFX_SELECTED OFF)

# OpenGL GFX handler.
if (AEON_GFX_GL)
    if (AEON_GFX_GLES2)
        message (FATAL_ERROR "AEON_GFX_GLES2 conflicts with AEON_GFX_GL renderer.")
    endif ()

    message ("Using OpenGL as graphics renderer.")
    set(AEON_HAS_GFX_SELECTED ON)
endif ()

# GLES2 GFX handler.
if (AEON_GFX_GLES2)
    if (AEON_GFX_GL)
        message (FATAL_ERROR "AEON_GFX_GL conflicts with AEON_GFX_GLES2 renderer.")
    endif ()

    message ("Using OpenGL ES 2.0 as graphics renderer.")
    set(AEON_HAS_GFX_SELECTED ON)
endif ()

# Check if any GFX handler was selected.
if (NOT AEON_HAS_GFX_SELECTED)
    message (FATAL_ERROR "No graphics renderer selected.")
endif ()

################################################################################

set(AEON_HAS_PLATFORM_SELECTED OFF)

# GLFW Platform
if (AEON_PLATFORM_GLFW)
    if (NOT AEON_GFX_GL)
        message (FATAL_ERROR "GLFW requires OpenGL; Please set AEON_GFX_GL.")
    endif()
    if (AEON_PLATFORM_RPI)
        message (FATAL_ERROR "AEON_PLATFORM_RPI conflicts with AEON_PLATFORM_GLFW platform.")
    endif()
    
    message ("Using GLFW as platform.")
    set(AEON_HAS_PLATFORM_SELECTED ON)
endif ()

# RPI Platform
if (AEON_PLATFORM_RPI)
    if (NOT AEON_GFX_GLES2)
        message (FATAL_ERROR "Raspberry Pi requires OpenGL ES 2.0; Please set AEON_GFX_GLES2.")
    endif()
    if (AEON_PLATFORM_GLFW)
        message (FATAL_ERROR "AEON_PLATFORM_GLFW conflicts with AEON_PLATFORM_RPI platform.")
    endif()
    
    message ("Using Raspberry Pi as platform.")
    set(AEON_HAS_PLATFORM_SELECTED ON)
endif ()

if (NOT AEON_HAS_PLATFORM_SELECTED)
    message (FATAL_ERROR "No platform was selected.")
endif ()

################################################################################

add_subdirectory(dep)
add_subdirectory(engine)
add_subdirectory(examples)
add_subdirectory(tests)

################################################################################

include(CopyToRuntimePath)

copy_folder_to_runtime_path(
    PATH bin
)
