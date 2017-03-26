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

message(STATUS "+------------------------------------------------------------------------------+")
message(STATUS "| Google Test                                                                  |")
message(STATUS "+------------------------------------------------------------------------------+")
add_subdirectory(googletest)

message(STATUS "+------------------------------------------------------------------------------+")
message(STATUS "| Zlib                                                                         |")
message(STATUS "+------------------------------------------------------------------------------+")
add_subdirectory(zlib)

message(STATUS "+------------------------------------------------------------------------------+")
message(STATUS "| PNG                                                                          |")
message(STATUS "+------------------------------------------------------------------------------+")
add_subdirectory(png)

if (AEON_GFX_GL)
    message(STATUS "+------------------------------------------------------------------------------+")
    message(STATUS "| GLEW                                                                         |")
    message(STATUS "+------------------------------------------------------------------------------+")
    add_subdirectory(glew)
endif ()

if (AEON_PLATFORM_GLFW)
    message(STATUS "+------------------------------------------------------------------------------+")
    message(STATUS "| GLFW                                                                         |")
    message(STATUS "+------------------------------------------------------------------------------+")
    add_subdirectory(glfw)
endif ()

message(STATUS "+------------------------------------------------------------------------------+")
message(STATUS "| GLM                                                                          |")
message(STATUS "+------------------------------------------------------------------------------+")
add_subdirectory(glm)

message(STATUS "+------------------------------------------------------------------------------+")
message(STATUS "| Open Asset Import Library                                                    |")
message(STATUS "+------------------------------------------------------------------------------+")
add_subdirectory(assimp)

message(STATUS "+------------------------------------------------------------------------------+")
message(STATUS "| json11                                                                       |")
message(STATUS "+------------------------------------------------------------------------------+")
add_subdirectory(json11)

message(STATUS "+------------------------------------------------------------------------------+")
message(STATUS "| Aeon                                                                         |")
message(STATUS "+------------------------------------------------------------------------------+")
add_subdirectory(libaeon/src)
add_subdirectory(libaeon/tests)

message(STATUS "+------------------------------------------------------------------------------+")
message(STATUS "| Finished submodules                                                          |")
message(STATUS "+------------------------------------------------------------------------------+")
