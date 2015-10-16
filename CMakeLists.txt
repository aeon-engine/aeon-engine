cmake_minimum_required(VERSION 3.1.0)
project(AeonEngine)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/dep/cmake/;${CMAKE_SOURCE_DIR}/CMake")
set(CMAKE_PREFIX_PATH "$ENV{AEON_LIBRARIES_PATH};${CMAKE_PREFIX_PATH}")

include(CompilerFlags)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

################################################################################

include(CTest)
enable_testing()

################################################################################

# Code coverage did not work on Xcode due to linker errors (missing libprofile_rt?)
if (NOT CMAKE_GENERATOR STREQUAL Xcode)
    if (APPLE)
        option(AEON_ENABLE_CLANG_COVERAGE "Compile with code coverage enabled for GCOV on OSX." ON)

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

set(Boost_USE_STATIC_LIBS        ON)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
find_package(Boost COMPONENTS
    system
    date_time
    filesystem
    regex
    unit_test_framework
    REQUIRED
)

find_package(OpenGL REQUIRED)
find_package(GLEW)
find_package(GLFW)
find_package(GLM)
find_package(ASSIMP)
find_package(ZLIB)
find_package(PNG)

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

option(AEON_GFX_GL "Use OpenGL as graphics renderer." ON)
option(AEON_PLATFORM_GLFW "Use GLFW as platform (creates the window and context)" ON)

################################################################################

if (AEON_GFX_GL)
    message ("Using OpenGL as graphics renderer.")
else ()
    message (FATAL_ERROR "No graphics renderer selected.")
endif ()

if (AEON_PLATFORM_GLFW)
    if (NOT AEON_GFX_GL)
        message (FATAL_ERROR "GLFW requires OpenGL; Please set AEON_GFX_GL.")
    endif()
    message ("Using GLFW as platform.")
else ()
    message (FATAL_ERROR "No platform selected.")
endif ()

################################################################################

add_subdirectory(dep)
add_subdirectory(engine)
add_subdirectory(game)

################################################################################

include(CopyToRuntimePath)

copy_folder_to_runtime_path(
    PATH bin
)

if (MSVC)
    copy_files_to_runtime_path(
        FILES
            ${GLEW_ROOT_DIR}/bin/glew32d.dll
            ${PNG_ROOT_DIR}/bin/libpng16d.dll
            ${ZLIB_ROOT_DIR}/bin/zlibd.dll
            ${ASSIMP_ROOT_DIR}/bin/assimpd.dll
        CONFIGURATIONS Debug
    )

    copy_files_to_runtime_path(
        FILES
            ${GLEW_ROOT_DIR}/bin/glew32.dll
            ${PNG_ROOT_DIR}/bin/libpng16.dll
            ${ZLIB_ROOT_DIR}/bin/zlib.dll
            ${ASSIMP_ROOT_DIR}/bin/assimp.dll
        CONFIGURATIONS Release
    )
endif ()
