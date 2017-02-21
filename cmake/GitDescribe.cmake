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

function(get_git_describe_tag git_describe_tag)
    if (NOT GIT_FOUND)
        find_package(Git REQUIRED)
    endif()

    execute_process(
        COMMAND ${GIT_EXECUTABLE} "describe" "--tags" "--long"
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_DESCRIBE_OUTPUT
        ERROR_VARIABLE GIT_DESCRIBE_ERROR_OUTPUT
        RESULT_VARIABLE GIT_DESCRIBE_RESULT
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    if (NOT GIT_DESCRIBE_RESULT EQUAL 0)
        message(FATAL_ERROR "Could not parse git describe version.\nOutput was ${GIT_DESCRIBE_ERROR_OUTPUT}")
    endif()

    set(${git_describe_tag} ${GIT_DESCRIBE_OUTPUT} PARENT_SCOPE)
endfunction()
