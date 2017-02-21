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

find_program(
    MONO_EXECUTABLE mono
    PATH $ENV{MONO_DEPENDENCIES_PREFIX}/bin
)

if (MSVC)
    find_program(
        MONO_MCS_EXECUTABLE mcs.bat
        PATH $ENV{MONO_DEPENDENCIES_PREFIX}/bin
    )
else ()
    find_program(
        MONO_MCS_EXECUTABLE mcs
        PATH $ENV{MONO_DEPENDENCIES_PREFIX}/bin
    )
endif ()

find_program(
    MONO_PKG_CONFIG_EXECUTABLE pkg-config
    PATH $ENV{MONO_DEPENDENCIES_PREFIX}/bin
)

find_library(
    MONO_MAIN_LIBRARY mono-2.0
    PATH $ENV{MONO_DEPENDENCIES_PREFIX}/lib
)

set(MONO_FOUND FALSE CACHE INTERNAL "")

if(MONO_EXECUTABLE AND MONO_MCS_EXECUTABLE AND MONO_PKG_CONFIG_EXECUTABLE AND MONO_MAIN_LIBRARY)
    set(MONO_FOUND TRUE CACHE INTERNAL "")

    get_filename_component(MONO_LIBRARY_PATH "${MONO_MAIN_LIBRARY}" DIRECTORY)
    set(MONO_LIBRARY_PATH "${MONO_LIBRARY_PATH}" CACHE PATH "")

    get_filename_component(MONO_INCLUDE_PATH "${MONO_LIBRARY_PATH}/../include/mono-2.0" ABSOLUTE)
    set(MONO_INCLUDE_PATH "${MONO_INCLUDE_PATH}" CACHE PATH "")
    set(MONO_ASSEMBLY_PATH "${MONO_LIBRARY_PATH}" CACHE PATH "")

    get_filename_component(MONO_CONFIG_PATH "${MONO_LIBRARY_PATH}/../etc" ABSOLUTE)
    set(MONO_CONFIG_PATH "${MONO_CONFIG_PATH}" CACHE PATH "")

    get_filename_component(MONO_BINARY_PATH "${MONO_LIBRARY_PATH}/../bin" ABSOLUTE)
    set(MONO_BINARY_PATH "${MONO_BINARY_PATH}" CACHE PATH "")

    set(MONO_LIBRARIES "${MONO_MAIN_LIBRARY}" CACHE STRING "")

    if (APPLE)
        find_library(CORE_FOUNDATION_LIBRARY CoreFoundation)
        set(MONO_LIBRARIES "${MONO_LIBRARIES};${CORE_FOUNDATION_LIBRARY}")
    endif ()

    if (MSVC)
        include(CopyToRuntimePath)
        find_file(MONO_DLL_PATH mono-2.0.dll PATH ${MONO_BINARY_PATH})
        copy_files_to_runtime_path(FILES ${MONO_DLL_PATH})
    endif ()

    execute_process(COMMAND "${MONO_MCS_EXECUTABLE}" "--version" OUTPUT_VARIABLE MONO_VERSION OUTPUT_STRIP_TRAILING_WHITESPACE)
    string(REGEX REPLACE ".*version ([^ ]+)" "\\1" MONO_VERSION "${MONO_VERSION}")
    message(STATUS "Found Mono version: ${MONO_MAIN_LIBRARY} (found version \"${MONO_VERSION}\")")
endif()

