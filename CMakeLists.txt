# Copyright (c) 2012-2017 Robin Degen
#
# Permission is hereby granted, free of charge, to any person
# obtaining a copy of this software and associated documentation
# files (the "Software"), to deal in the Software without
# restriction, including without limitation the rights to use,
# copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following
# conditions:
#
# The above copyright notice and this permission notice shall be
# included in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
# OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
# HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
# WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
# OTHER DEALINGS IN THE SOFTWARE.

cmake_minimum_required(VERSION 3.2.0)
project(AeonEngine)

if (NOT AEON_CMAKE_INFRA_PATH)
    set(AEON_CMAKE_INFRA_PATH "${CMAKE_SOURCE_DIR}/dep/cmake/")
endif ()

if (NOT AEON_ENGINE_ROOT)
    set(AEON_ENGINE_ROOT ${CMAKE_SOURCE_DIR})
endif ()

################################################################################

# Perform a sanity check on submodules; and inform the user if they are missing.
file(GLOB RESULT "${AEON_CMAKE_INFRA_PATH}/*.cmake")
list(LENGTH RESULT RES_LEN)
if(RES_LEN EQUAL 0)
    message ("Could not find Aeon Cmake infra.")
    message ("The most likely cause is that you forgot to download and checkout the git submodules.")
    message ("Please run the following command in the root of the repository and try again:")
    message ("git submodule update --init")
    message (FATAL_ERROR "Aborting due to missing Cmake infra.")
endif()

################################################################################

set(CMAKE_MODULE_PATH "${AEON_CMAKE_INFRA_PATH};${CMAKE_MODULE_PATH}")

include(CompilerFlags)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_CONFIGURATION_TYPES Debug Release CACHE TYPE INTERNAL FORCE)

set(CMAKE_DEBUG_POSTFIX "_d")

set(CMAKE_CXX_STANDARD 14)

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

# If mono is found on the system; attempt to build with it enabled.
find_package(Mono)
if (MONO_FOUND)
    set(AEON_ENABLE_MONO ON CACHE BOOL "")
endif ()

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
