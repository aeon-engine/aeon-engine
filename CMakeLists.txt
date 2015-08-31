cmake_minimum_required(VERSION 3.0.1)
project(AeonEngine)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/dep/cmake/;${CMAKE_SOURCE_DIR}/CMake")
set(CMAKE_PREFIX_PATH "$ENV{AEON_LIBRARIES_PATH};${CMAKE_PREFIX_PATH}")

################################################################################

if (NOT MSVC)
    set(CMAKE_CXX_FLAGS "-stdlib=libc++ -std=c++1y ${CMAKE_CXX_FLAGS}")
endif (NOT MSVC)

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

add_subdirectory(dep)
add_subdirectory(aeon_engine)

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
