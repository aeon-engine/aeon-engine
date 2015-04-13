cmake_minimum_required(VERSION 3.1)
project(AeonEngine)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")

if (NOT MSVC)
    list(APPEND CMAKE_CXX_FLAGS "-std=c++1y ${CMAKE_CXX_FLAGS}")
endif (NOT MSVC)

set(Boost_ADDITIONAL_VERSIONS "1.57" "1.57.0")
set(Boost_USE_STATIC_LIBS        ON)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
find_package (Boost COMPONENTS
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

add_subdirectory(dep)
add_subdirectory(aeon_engine)
