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

# Mono
option(AEON_ENABLE_MONO "Enable the Aeon Mono library." OFF)
option(AEON_COPY_MONO_RUNTIMES "Enable if Mono should be embedded and ran purely from the binary folder." OFF)

# Sockets
option(AEON_ENABLE_SOCKETS "Enable the Aeon Socket library." OFF)

# Midi
option(AEON_ENABLE_MIDI "Enable the Aeon Midi IO library." OFF)

# HDF5
option(AEON_ENABLE_HDF5 "Enable the Aeon HDF5 wrapper library." OFF)

################################################################################

set(LIB_AEON_STREAMS_SOURCE
    aeon/streams.h
    aeon/streams/config.h
    aeon/streams/access_mode_mixin.h
    aeon/streams/stream_reader.h
    aeon/streams/stream_writer.h
    aeon/streams/stream.h
    aeon/streams/file_stream.h
    aeon/streams/file_stream.cpp
    aeon/streams/io_stream.h
    aeon/streams/io_stream.cpp
    aeon/streams/circular_buffer_stream.h
    aeon/streams/memory_stream.h
    aeon/streams/stream_name_mixin.h
    aeon/streams/io_stream_colors_mixin.h
    aeon/streams/io_stream_colors_mixin.cpp
)

source_group(streams FILES ${LIB_AEON_STREAMS_SOURCE})

################################################################################

set(LIB_AEON_MATH_SOURCE
    aeon/math.h
    aeon/math/perlin_noise.h
    aeon/math/perlin_noise.cpp
    aeon/math/simplex_noise.h
    aeon/math/simplex_noise.cpp
)

source_group(math FILES ${LIB_AEON_MATH_SOURCE})

################################################################################

if (AEON_ENABLE_SOCKETS)
    set(LIB_AEON_SOCKETS_SOURCE
        aeon/sockets.h
        aeon/sockets/config.h
        aeon/sockets/line_protocol_handler.h
        aeon/sockets/tcp_server.h
    )

    source_group(sockets FILES ${LIB_AEON_SOCKETS_SOURCE})

    set(LIB_AEON_WEBSERVER_SOURCE
        aeon/webserver.h
        aeon/webserver/http_protocol_handler.h
        aeon/webserver/http_protocol_handler.cpp
        aeon/webserver/http_request.h
        aeon/webserver/http_request.cpp
    )

    source_group(webserver FILES ${LIB_AEON_WEBSERVER_SOURCE})
endif ()

################################################################################

set(LIB_AEON_UTILITY_SOURCE
    aeon/utility.h
    aeon/utility/asynchronizer.h
    aeon/utility/bitflags.h
    aeon/utility/singleton.h
    aeon/utility/configfile.h
    aeon/utility/configfile.cpp
    aeon/utility/container.h
    aeon/utility/hexdump.h
    aeon/utility/hexdump.cpp
    aeon/utility/endianness.h
    aeon/utility/timer.cpp
    aeon/utility/timer.h
    aeon/utility/optional.h
    aeon/utility/linear_map.h
    aeon/utility/variant.h
    aeon/utility/noncopyable.h
    aeon/utility/string_traits.h
    aeon/utility/string.cpp
    aeon/utility/string.h
    aeon/utility/listener_subject.h
    aeon/utility/dispatcher.h
    aeon/utility/signals.h
    aeon/utility/parallelizer.h
    aeon/utility/literals.h
)

source_group(utility FILES ${LIB_AEON_UTILITY_SOURCE})

################################################################################

set(LIB_AEON_PLATFORM_SOURCE
    aeon/platform.h
    aeon/platform/platform.h
    aeon/platform/term_colors.h
    aeon/platform/compilers.h
)

source_group(platform FILES ${LIB_AEON_PLATFORM_SOURCE})

################################################################################

set(LIB_AEON_TESTING_SOURCE
    aeon/testing.h
    aeon/testing/temporary_file_fixture.h
    aeon/testing/temporary_file_fixture.cpp
)

source_group(testing FILES ${LIB_AEON_TESTING_SOURCE})

################################################################################

set(LIB_AEON_FILESYSTEM_SOURCE
    aeon/filesystem.h
    aeon/filesystem/filesystem.h
    aeon/filesystem/filesystem.cpp
)

source_group(filesystem FILES ${LIB_AEON_FILESYSTEM_SOURCE})

################################################################################

set(LIB_AEON_LOGGER_SOURCE
    aeon/logger.h
    aeon/logger/logger.h
    aeon/logger/log_sink.h
    aeon/logger/log_level.h
    aeon/logger/base_backend.h
    aeon/logger/simple_backend.h
    aeon/logger/simple_sink_backend.h
    aeon/logger/multithreaded_sink_backend.h
    aeon/logger/stream_sink.h
    aeon/logger/io_stream_sink.h
)

source_group(logger FILES ${LIB_AEON_LOGGER_SOURCE})

################################################################################

if (AEON_ENABLE_CURL)
    set(LIB_AEON_CURL_SOURCE
        aeon/curl.h
        aeon/curl/url_downloader.h
        aeon/curl/url_downloader.cpp
        aeon/curl/exceptions.h
        aeon/curl/global_wrapper.cpp
        aeon/curl/global_wrapper.h
        aeon/curl/easy_wrapper.cpp
        aeon/curl/easy_wrapper.h
    )

    source_group(curl FILES ${LIB_AEON_CURL_SOURCE})
endif ()

################################################################################

if (AEON_ENABLE_MONO)
    include(Mono)

    if (AEON_COPY_MONO_RUNTIMES)
        copy_mono_runtimes_to_runtime_path()
        set(_MONO_ASSEMBLY_DIR ".")
        set(_MONO_CONFIG_DIR ".")
    else ()
        set(_MONO_ASSEMBLY_DIR ${MONO_ASSEMBLY_PATH})
        set(_MONO_CONFIG_DIR ${MONO_CONFIG_PATH})
    endif ()

    set(AEON_MONO_ASSEMBLY_DIR "${_MONO_ASSEMBLY_DIR}"
        CACHE PATH "Path to the Mono assembly dir (mono/lib). May be a relative path.")
    set(AEON_MONO_CONFIG_DIR "${_MONO_CONFIG_DIR}"
        CACHE PATH "Path to the Mono config dir (mono/etc). May be a relative path.")

    configure_file(src/aeon/mono/mono_build_config.h.in mono_build_config.h @ONLY)

    set(LIB_AEON_MONO_SOURCE
        aeon/mono.h
        aeon/mono/mono_method.cpp
        aeon/mono/mono_method.h
        aeon/mono/mono_assembly.cpp
        aeon/mono/mono_assembly.h
        aeon/mono/mono_jit.cpp
        aeon/mono/mono_jit.h
        aeon/mono/mono_class.cpp
        aeon/mono/mono_class.h
        aeon/mono/mono_object.cpp
        aeon/mono/mono_object.h
        aeon/mono/mono_string.cpp
        aeon/mono/mono_string.h
        aeon/mono/mono_gchandle.cpp
        aeon/mono/mono_gchandle.h
        aeon/mono/mono_class_instance.cpp
        aeon/mono/mono_class_instance.h
        aeon/mono/mono_exception.h
        ${CMAKE_CURRENT_BINARY_DIR}/mono_build_config.h
    )

    source_group(mono FILES ${LIB_AEON_MONO_SOURCE})
endif ()

################################################################################

if (AEON_ENABLE_MIDI)
    set(LIB_AEON_MIDI_SOURCE
        aeon/midi.h
        aeon/midi/midi_device.cpp
        aeon/midi/midi_device.h
        aeon/midi/midi_file_reader.cpp
        aeon/midi/midi_file_reader.h
        aeon/midi/midi_input_device.cpp
        aeon/midi/midi_input_device.h
        aeon/midi/midi_input_manager.cpp
        aeon/midi/midi_input_manager.h
        aeon/midi/midi_output_device.cpp
        aeon/midi/midi_output_device.h
        aeon/midi/midi_messages.h
    )

    source_group(midi FILES ${LIB_AEON_MIDI_SOURCE})
endif ()

################################################################################

if (AEON_ENABLE_HDF5)
    set(LIB_AEON_HDF5_SOURCE
        aeon/hdf5.h
        aeon/hdf5/hdf5_file.h
        aeon/hdf5/hdf5_file_impl.h
        aeon/hdf5/hdf5_dataset.h
        aeon/hdf5/hdf5_dataset_impl.h
        aeon/hdf5/hdf5_dataset_wrapper.h
        aeon/hdf5/hdf5_dataset_wrapper_impl.h
        aeon/hdf5/hdf5_dataset_properties.h
        aeon/hdf5/hdf5_dataset_properties_impl.h
        aeon/hdf5/hdf5_dataspace.h
        aeon/hdf5/hdf5_dataspace_impl.h
        aeon/hdf5/hdf5_datatype.h
        aeon/hdf5/hdf5_datatype_impl.h
        aeon/hdf5/hdf5_scoped_create_group.h
        aeon/hdf5/hdf5_scoped_create_group_impl.h
        aeon/hdf5/hdf5_object.h
        aeon/hdf5/hdf5_object_impl.h
        aeon/hdf5/hdf5_object_iterator.h
        aeon/hdf5/hdf5_object_iterator_impl.h
    )

    source_group(hdf5 FILES ${LIB_AEON_HDF5_SOURCE})
endif ()

################################################################################

set(LIB_AEON_SOURCE
    ${LIB_AEON_STREAMS_SOURCE}
    ${LIB_AEON_MATH_SOURCE}
    ${LIB_AEON_UTILITY_SOURCE}
    ${LIB_AEON_PLATFORM_SOURCE}
    ${LIB_AEON_LOGGER_SOURCE}
    ${LIB_AEON_FILESYSTEM_SOURCE}
    ${LIB_AEON_TESTING_SOURCE}
)

if (AEON_ENABLE_CURL)
    list(APPEND LIB_AEON_SOURCE ${LIB_AEON_CURL_SOURCE})
endif ()

if (AEON_ENABLE_SOCKETS)
    list(APPEND LIB_AEON_SOURCE
        ${LIB_AEON_SOCKETS_SOURCE}
        ${LIB_AEON_WEBSERVER_SOURCE}
    )
endif ()

if (AEON_ENABLE_MONO)
    list(APPEND LIB_AEON_SOURCE ${LIB_AEON_MONO_SOURCE})
endif ()

if (AEON_ENABLE_MIDI)
    list(APPEND LIB_AEON_SOURCE ${LIB_AEON_MIDI_SOURCE})
endif ()

if (AEON_ENABLE_HDF5)
    list(APPEND LIB_AEON_SOURCE ${LIB_AEON_HDF5_SOURCE})
endif ()

add_library(aeon ${LIB_AEON_SOURCE})

set_target_properties(aeon PROPERTIES
    FOLDER dep/libaeon
)

target_include_directories(aeon PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

if (AEON_ENABLE_CURL)
    message(STATUS "Building libAeon with CURL support.")
    target_link_libraries(aeon curl)
endif ()

if (AEON_ENABLE_SOCKETS)
    message(STATUS "Building libAeon with Sockets support (Asio).")
    target_link_libraries(aeon asio)
endif ()

if (AEON_ENABLE_MONO)
    message(STATUS "Building libAeon with MONO support.")
    target_link_libraries(aeon ${MONO_LIBRARIES})
    target_include_directories(aeon PUBLIC ${MONO_INCLUDE_PATH} ${CMAKE_CURRENT_BINARY_DIR})
endif ()

if (AEON_ENABLE_MIDI)
    message(STATUS "Building libAeon with MIDI support.")
    target_link_libraries(aeon rtmidi)
endif ()

if (AEON_ENABLE_HDF5)
    message(STATUS "Building libAeon with HDF5 wrapper support.")
    target_link_libraries(aeon hdf5-static hdf5_hl-static)
endif ()

install(
    TARGETS aeon
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

install(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    DESTINATION include
    FILES_MATCHING PATTERN "*.h"
)

