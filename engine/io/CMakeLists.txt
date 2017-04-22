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

set (AEON_ENGINE_IO_SOURCES
    include/aeon/io/io_exception.h
    include/aeon/io/io_file_interface.h
    include/aeon/io/io_file_open_mode.h
    include/aeon/io/io_filesystem_interface.h
    include/aeon/io/io_interface.h
)

source_group(io FILES ${AEON_ENGINE_IO_SOURCES})

set (AEON_ENGINE_IO_GENERIC_SOURCES
    include/aeon/io/generic/io_generic_file_interface.h
    include/aeon/io/generic/io_generic_filesystem_interface.h
    src/generic/io_generic_file_interface.cpp
    src/generic/io_generic_filesystem_interface.cpp
)

source_group(io\\generic FILES ${AEON_ENGINE_IO_GENERIC_SOURCES})

add_library(aeon_engine_io STATIC
    ${AEON_ENGINE_IO_SOURCES}
    ${AEON_ENGINE_IO_GENERIC_SOURCES}
)

target_link_libraries(aeon_engine_io
    aeon_streams
    aeon_logger
    aeon_filesystem
    aeon_engine_common
)

target_include_directories(aeon_engine_io
    PUBLIC include
)

set_target_properties(
    aeon_engine_io PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    FOLDER engine
)

install(
    TARGETS aeon_engine_io
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

install(
    DIRECTORY include/
    DESTINATION include
    FILES_MATCHING PATTERN "*.h"
)

