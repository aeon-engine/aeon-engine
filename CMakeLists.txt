cmake_minimum_required(VERSION 3.2.1)
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
# GFX options
################################################################################
set(AEON_GFX_RENDERER_NAME_OPENGL3_3 "OpenGL3.3")
set(AEON_GFX_RENDERER_NAME_GLES2 "GLES2")

set(AEON_GFX_GL OFF)
set(AEON_GFX_GLES2 OFF)

set(AEON_GFX_RENDERER ${AEON_GFX_RENDERER_NAME_OPENGL3_3} CACHE STRING "GFX Render backend")
set_property(CACHE AEON_GFX_RENDERER PROPERTY STRINGS ${AEON_GFX_RENDERER_NAME_OPENGL3_3} ${AEON_GFX_RENDERER_NAME_GLES2})

if (AEON_GFX_RENDERER STREQUAL AEON_GFX_RENDERER_NAME_OPENGL3_3)
    message(STATUS "Using OpenGL as graphics renderer.")

    find_package(OpenGL REQUIRED)

    set(AEON_GFX_GL ON)
elseif (AEON_GFX_RENDERER STREQUAL AEON_GFX_RENDERER_NAME_GLES2)
    message (STATUS "Using OpenGL ES 2.0 as graphics renderer.")

    set(AEON_GFX_GLES2 ON)
else ()
    message (FATAL_ERROR "No valid graphics renderer selected.")
endif ()

################################################################################
# Platform options
################################################################################
set(AEON_PLATFORM_NAME_GLFW "GLFW")
set(AEON_PLATFORM_NAME_RPI "RaspberryPi")
set(AEON_PLATFORM_NAME_IOS "IOS")

set(AEON_PLATFORM_GLFW OFF)
set(AEON_PLATFORM_RPI OFF)
set(AEON_PLATFORM_IOS OFF)

set(AEON_PLATFORM ${AEON_PLATFORM_NAME_GLFW} CACHE STRING "Platform backend")

set_property(
    CACHE AEON_PLATFORM PROPERTY STRINGS
    ${AEON_PLATFORM_NAME_GLFW}
    ${AEON_PLATFORM_NAME_RPI}
    ${AEON_PLATFORM_NAME_IOS}
)

if (AEON_PLATFORM STREQUAL AEON_PLATFORM_NAME_GLFW)
    message (STATUS "Using GLFW as platform.")
    set(AEON_PLATFORM_GLFW ON)
elseif (AEON_PLATFORM STREQUAL AEON_PLATFORM_NAME_RPI)
    if (NOT AEON_GFX_GLES2)
        message (FATAL_ERROR "Raspberry Pi requires OpenGL ES 2.0; Please set AEON_GFX_RENDERER to GLES2")
    endif ()

    message (STATUS "Using Raspberry Pi as platform.")

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

    set(AEON_PLATFORM_RPI ON)
elseif (AEON_PLATFORM STREQUAL AEON_PLATFORM_NAME_IOS)
    if (NOT AEON_GFX_GLES2)
        message (FATAL_ERROR "iOS requires OpenGL ES 2.0; Please set AEON_GFX_RENDERER to GLES2")
    endif ()

    if (NOT CMAKE_GENERATOR STREQUAL "Xcode")
        message (FATAL_ERROR "iOS requires Xcode as CMake generator.")
    endif ()

    message (STATUS "Using iOS as platform.")

    set(XCODE_ATTRIBUTE_SDKROOT iphoneos)
    set(CMAKE_OSX_SYSROOT iphoneos)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework Foundation -framework CoreGraphics -framework QuartzCore -framework UIKit -framework OpenGLES")
    set(XCODE_ATTRIBUTE_GCC_UNROLL_LOOPS "YES")
    set(XCODE_ATTRIBUTE_LLVM_VECTORIZE_LOOPS "YES")
    set(XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "iPhone Developer")
    set(XCODE_ATTRIBUTE_GCC_PRECOMPILE_PREFIX_HEADER "YES")
    set(MACOSX_BUNDLE_GUI_IDENTIFIER "nl.robindegen.\${PRODUCT_NAME:rfc1034identifier}")
    set(CMAKE_OSX_ARCHITECTURES "$(ARCHS_UNIVERSAL_IPHONE_OS)")
    set(CMAKE_MACOSX_BUNDLE YES)
    set(CMAKE_XCODE_ATTRIBUTE_CODE_SIGNING_REQUIRED "NO")

    set(AEON_PLATFORM_IOS ON)
else ()
    message (FATAL_ERROR "No valid platform was selected.")
endif ()

################################################################################
# Debugging options
################################################################################

# Check and log all OpenGL 3 and GLES 2 errors. Warning: This is very slow,
# only use for debugging purposes.
option(AEON_ENABLE_GL_ERROR_CHECKS "Check and log all OpenGL 3 and GLES 2 errors." ON)

################################################################################

if (APPLE AND NOT AEON_PLATFORM STREQUAL AEON_PLATFORM_NAME_IOS)
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
add_subdirectory(engine)
add_subdirectory(examples)
add_subdirectory(tests)

################################################################################

include(CopyToRuntimePath)

copy_folder_to_runtime_path(
    PATH bin
)
