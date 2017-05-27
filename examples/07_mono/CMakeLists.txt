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

include(Utility)
include(Mono)

if (MSVC)
    include_external_msproject(
        MonoGame
        ${CMAKE_CURRENT_SOURCE_DIR}/MonoGame/MonoGame.csproj
        TYPE FAE04EC0-301F-11D3-BF4B-00C04F79EFBC
    )
else ()
    add_mono_assembly(
        TARGET MonoGame
        DESTINATION ${CMAKE_BINARY_DIR}/bin
        TYPE library
        SOURCES MonoGame/MonoApplication.cs
        ADDITIONAL_ARGS "/reference:AeonEngineMono.dll"
    )
endif ()

add_dependencies(MonoGame AeonEngineMono)

add_executable(example_07_mono main.cpp application.cpp application.h)

target_include_directories(example_07_mono
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(example_07_mono aeon_engine_mono)

set_target_properties(
    example_07_mono PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    FOLDER examples
)

set_working_dir(example_07_mono "${CMAKE_SOURCE_DIR}/bin")

install(
    TARGETS example_07_mono
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)
