# Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

cmake_minimum_required(VERSION 3.14)

if (DEFINED ENV{AEON_ENGINE_PROJECT_NAME})
    project($ENV{AEON_ENGINE_PROJECT_NAME})
else ()
    project(AeonEngine)
endif ()

# Don't allow any circular dependencies. Not even for static libraries.
set_property(GLOBAL PROPERTY GLOBAL_DEPENDS_NO_CYCLES 1)

################################################################################

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/dep/cmake/;${CMAKE_MODULE_PATH}")

include(Dependencies)
handle_local_dependencies_file()

include(CompilerFlags)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_CXX_STANDARD 17)

################################################################################

include(CTest)
enable_testing()

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

include(ComponentUtils)
enable_component(common)
enable_component(fonts)
enable_component(imaging)
enable_component(logger)
enable_component(math)
enable_component(plugins)
enable_component(ptree)
enable_component(reflection)
enable_component(streams)
enable_component(unicode)
enable_component(utility)

find_package(Mono)
if (MONO_FOUND)
    enable_component(mono)
endif ()

set(AEON_ENABLE_IMAGING ON CACHE BOOL "")
set(AEON_ENABLE_FONTS ON CACHE BOOL "")

################################################################################

add_subdirectory(dep)
add_subdirectory(engine)
add_subdirectory(examples)
add_subdirectory(experimental)
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
