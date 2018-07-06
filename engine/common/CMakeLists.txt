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

set (AEON_ENGINE_COMMON_SOURCES
    include/aeon/common/cached_object.h
    include/aeon/common/exception.h
    include/aeon/common/has_z_order.h
    include/aeon/common/logger.h
    include/aeon/common/object_cache.h
    src/logger.cpp
)

source_group(common FILES ${AEON_ENGINE_COMMON_SOURCES})

set (AEON_ENGINE_COMMON_TYPES_SOURCES
    include/aeon/common/types/color.h
    include/aeon/common/types/rectangle.h
    src/types/color.cpp
)

source_group(common\\types FILES ${AEON_ENGINE_COMMON_TYPES_SOURCES})

add_library(aeon_engine_common STATIC
    ${AEON_ENGINE_COMMON_SOURCES}
    ${AEON_ENGINE_COMMON_TYPES_SOURCES}
)

target_link_libraries(aeon_engine_common
    aeon_common
    aeon_utility
    aeon_logger
    aeon_streams
    aeon_math
)

target_include_directories(aeon_engine_common
    PUBLIC include
    PRIVATE ${CMAKE_BINARY_DIR}
)

set_target_properties(
    aeon_engine_common PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    FOLDER engine
)

install(
    TARGETS aeon_engine_common
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

install(
    DIRECTORY include/
    DESTINATION include
    FILES_MATCHING PATTERN "*.h"
)

