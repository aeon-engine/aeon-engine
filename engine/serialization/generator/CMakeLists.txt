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

file(GLOB AEON_ENGINE_SERIALIZATION_GENERATOR_DATA
    RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/objects 
    objects/*.json
)

file(TO_CMAKE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/objects AEON_ENGINE_SERIALIZATION_GENERATOR_DATA_PATH)
file(TO_CMAKE_PATH ${CMAKE_BINARY_DIR} AEON_ENGINE_SERIALIZATION_GENERATOR_DESTINATION)

configure_file(generator_objects.h.in ${CMAKE_CURRENT_BINARY_DIR}/generator_objects.h @ONLY)

################################################################################

set(AEON_ENGINE_SERIALIZATION_GENERATOR_SOURCES
    src/application.cpp
    src/application.h
    src/generator.cpp
    src/generator.h
    src/main.cpp
    src/parser.cpp
    src/parser.h
    src/object.h
    src/code_generator.h
    src/subtype_code_generator.cpp
    src/subtype_code_generator.h
)

source_group(serialization FILES ${AEON_ENGINE_SERIALIZATION_GENERATOR_SOURCES})

################################################################################

set(AEON_ENGINE_SERIALIZATION_GENERATOR_CODE_GENERATOR_SOURCES
    src/code_generators/code_generator_int.cpp
    src/code_generators/code_generator_int.h
    src/code_generators/code_generator_float.cpp
    src/code_generators/code_generator_float.h
    src/code_generators/code_generator_string.cpp
    src/code_generators/code_generator_string.h
    src/code_generators/code_generator_color.cpp
    src/code_generators/code_generator_color.h
    src/code_generators/code_generator_kvstring.cpp
    src/code_generators/code_generator_kvstring.h
    src/code_generators/code_generator_vec3.cpp
    src/code_generators/code_generator_vec3.h
    src/code_generators/code_generator_quaternion.cpp
    src/code_generators/code_generator_quaternion.h
    src/code_generators/code_generator_rectangle.cpp
    src/code_generators/code_generator_rectangle.h
)

source_group(serialization\\code_generators FILES ${AEON_ENGINE_SERIALIZATION_GENERATOR_CODE_GENERATOR_SOURCES})

################################################################################

add_executable(aeon_engine_serialization_generator
    ${AEON_ENGINE_SERIALIZATION_GENERATOR_SOURCES}
    ${AEON_ENGINE_SERIALIZATION_GENERATOR_CODE_GENERATOR_SOURCES}
)

target_link_libraries(aeon_engine_serialization_generator
    json11
    aeon_common
    aeon_streams
    aeon_filesystem
)

target_include_directories(aeon_engine_serialization_generator
    PRIVATE
        src
        ${CMAKE_CURRENT_BINARY_DIR}
)

set_target_properties(
    aeon_engine_serialization_generator PROPERTIES
    FOLDER engine/serialization
)

add_custom_target(aeon_engine_serialization_generator_runner
    aeon_engine_serialization_generator
    COMMENT "Running Serialization Generator." VERBATIM
)

set_target_properties(
    aeon_engine_serialization_generator_runner PROPERTIES
    FOLDER engine/serialization
)

add_dependencies(aeon_engine_serialization_generator_runner aeon_engine_serialization_generator)
