# Copyright (c) 2012-2018 Robin Degen
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

set (AEON_ENGINE_SERIALIZATION_SOURCES
    include/aeon/serialization/serialization.h
    src/serialization.cpp
)

source_group(serialization FILES ${AEON_ENGINE_SERIALIZATION_SOURCES})

add_library(aeon_engine_serialization STATIC
    ${AEON_ENGINE_SERIALIZATION_SOURCES}
)

target_link_libraries(aeon_engine_serialization
    aeon_engine_common
    aeon_common
    aeon_math
    Json11::Json11
)

target_include_directories(aeon_engine_serialization
    PUBLIC
        include
        ${CMAKE_BINARY_DIR}
)

set_target_properties(
    aeon_engine_serialization PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    FOLDER engine/serialization
)

install(
    TARGETS aeon_engine_serialization
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

install(
    DIRECTORY include/
    DESTINATION include
    FILES_MATCHING PATTERN "*.h"
)

add_dependencies(aeon_engine_serialization aeon_engine_serialization_generator_runner)
