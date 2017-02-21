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

include(CMakeParseArguments)
include(CopyToRuntimePath)

if (NOT MONO_FOUND)
    message(FATAL_ERROR "Mono is required for this CMake script. Please use find_package(Mono) before including.")
endif ()

function(add_mono_assembly)
    cmake_parse_arguments(
        MONO_ASSEMBLY_PARSED_ARGS
        ""
        "TARGET;DESTINATION;TYPE"
        "SOURCES"
        ${ARGN}
    )

    if (NOT MONO_ASSEMBLY_PARSED_ARGS_TYPE)
        set(MONO_ASSEMBLY_PARSED_ARGS_TYPE "library")
        message("No type provided for ${MONO_ASSEMBLY_PARSED_ARGS_TARGET}. Assuming library.")
    endif ()

    set(_FILE_EXTENSION "")
    if (MONO_ASSEMBLY_PARSED_ARGS_TYPE STREQUAL "library")
        set(_FILE_EXTENSION ".dll")
    elseif (MONO_ASSEMBLY_PARSED_ARGS_TYPE STREQUAL "exe")
        set(_FILE_EXTENSION ".exe")
    else ()
        message(FATAL_ERROR "Type must be either exe or library.")
    endif ()

    set(FULL_PATH_SOURCES "")
    foreach(_SOURCE ${MONO_ASSEMBLY_PARSED_ARGS_SOURCES})
        get_filename_component(_FULL_PATH "${SOURCE}" ABSOLUTE)
        list(APPEND FULL_PATH_SOURCES "${_FULL_PATH}/${_SOURCE}")
    endforeach()

    if (NOT MONO_ASSEMBLY_PARSED_ARGS_DESTINATION)
        set(MONO_ASSEMBLY_PARSED_ARGS_DESTINATION ${CMAKE_BINARY_DIR})
    endif ()

    file(MAKE_DIRECTORY ${MONO_ASSEMBLY_PARSED_ARGS_DESTINATION})

    #Dotnet package config disabled, since it only works properly on 32-bit.
    #get_mono_pkg_config("dotnet" MONO_DOTNET_PKG_CONFIG)

    add_custom_target(
        ${MONO_ASSEMBLY_PARSED_ARGS_TARGET} ALL
        ${MONO_MCS_EXECUTABLE} "-t:${MONO_ASSEMBLY_PARSED_ARGS_TYPE}" "${FULL_PATH_SOURCES}" "-out:${MONO_ASSEMBLY_PARSED_ARGS_TARGET}${_FILE_EXTENSION}"
        WORKING_DIRECTORY "${MONO_ASSEMBLY_PARSED_ARGS_DESTINATION}"
        COMMENT "Building Mono Library ${MONO_ASSEMBLY_PARSED_ARGS_TARGET}"
        SOURCES ${FULL_PATH_SOURCES}
    )

    # In Visual Studio and Xcode, the Bin folder is appended with Debug or Release.
    if (MSVC OR CMAKE_GENERATOR STREQUAL Xcode)
        file(MAKE_DIRECTORY ${MONO_ASSEMBLY_PARSED_ARGS_DESTINATION}/Debug)
        file(MAKE_DIRECTORY ${MONO_ASSEMBLY_PARSED_ARGS_DESTINATION}/Release)
        add_custom_command(TARGET ${MONO_ASSEMBLY_PARSED_ARGS_TARGET} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different ${MONO_ASSEMBLY_PARSED_ARGS_DESTINATION}/${MONO_ASSEMBLY_PARSED_ARGS_TARGET}${_FILE_EXTENSION} ${MONO_ASSEMBLY_PARSED_ARGS_DESTINATION}/Debug/${MONO_ASSEMBLY_PARSED_ARGS_TARGET}${_FILE_EXTENSION}
            COMMAND ${CMAKE_COMMAND} -E copy_if_different ${MONO_ASSEMBLY_PARSED_ARGS_DESTINATION}/${MONO_ASSEMBLY_PARSED_ARGS_TARGET}${_FILE_EXTENSION} ${MONO_ASSEMBLY_PARSED_ARGS_DESTINATION}/Release/${MONO_ASSEMBLY_PARSED_ARGS_TARGET}${_FILE_EXTENSION}
            WORKING_DIRECTORY "${MONO_ASSEMBLY_PARSED_ARGS_DESTINATION}"
            COMMENT "Duplicating ${MONO_ASSEMBLY_PARSED_ARGS_TARGET}${_FILE_EXTENSION} to the Debug and Release folders."
            VERBATIM
        )
    endif ()
endfunction()

function(copy_mono_runtimes_to_runtime_path)
    message(STATUS "Copying Mono runtimes to the runtime path.")
    copy_folder_to_runtime_path(
        PATH ${MONO_LIBRARY_PATH}/mono
        DESTINATION mono
    )
endfunction()

function(get_mono_pkg_config package output)
    execute_process(COMMAND "${MONO_PKG_CONFIG_EXECUTABLE}" "--libs" ${package} OUTPUT_VARIABLE _OUTPUT OUTPUT_STRIP_TRAILING_WHITESPACE)
    string(REPLACE " " ";" _OUTPUT "${_OUTPUT}")
    set(${output} ${_OUTPUT} PARENT_SCOPE)
endfunction()

