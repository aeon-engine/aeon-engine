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

set(AEON_CMAKE_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR})

macro(add_source_path target dir)
    set(source_files "")
    file(
        GLOB source_files
        RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
            ${dir}/*.cpp
            ${dir}/*.c
            ${dir}/*.mm
            ${dir}/*.h
    )
    list(APPEND ${target} "${source_files}")
endmacro()

macro(generate_source_groups sources)
    foreach(f ${sources})
        string(REGEX REPLACE "(.*)(/[^/]*)$" "\\1" source_group_name ${f})
        string(REPLACE / \\ source_group_name ${source_group_name})
        source_group("${source_group_name}" FILES ${f})
    endforeach()
endmacro()

function(set_working_dir target dir)
    message(STATUS "Setting working dir for target ${target} to ${dir}")

    if (MSVC)
        if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 19.0 AND NOT ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
            message(STATUS "set_working_dir requires Visual Studio 2015 or higher. Skipping.")
        else ()
            get_filename_component(absolute_dir "${dir}" ABSOLUTE)
            file(TO_NATIVE_PATH "${absolute_dir}" WORKING_DIR)
            configure_file(${AEON_CMAKE_ROOT_DIR}/VisualStudioWorkingDir.vcxproj.user.in ${target}.vcxproj.user @ONLY)
        endif ()
    endif ()
endfunction()
