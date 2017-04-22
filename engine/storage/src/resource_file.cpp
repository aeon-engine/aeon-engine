/*
 * Copyright (c) 2012-2017 Robin Degen
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include <aeon/io/io_filesystem_interface.h>
#include <aeon/storage/resource_file.h>
#include <aeon/common/compilers.h>
#include <string.h>
#include <cstdint>

namespace aeon
{
namespace storage
{

#define RESOURCE_FILE_MAJOR_VERSION 1
#define RESOURCE_FILE_MINOR_VERSION 0

#define RESOURCE_FILE_CHUNK_NAME_MAX_LEN 88
#define RESOURCE_FILE_DEFAULT_RESERVE_ALIGNMENT (8 * 1024)

AEON_PACK_STRUCT_PUSH(1)
struct resource_file_index_chunk
{
    std::uint8_t name[RESOURCE_FILE_CHUNK_NAME_MAX_LEN];
    std::uint32_t type_id;
    std::uint32_t flags;
    std::uint64_t offset;
    std::uint64_t reserved_size;
    std::uint64_t compressed_size;
    std::uint64_t actual_size;
} AEON_PACK_STRUCT_POP(1);

AEON_PACK_STRUCT_PUSH(1)
struct resource_file_header
{
    std::uint32_t magic;
    std::uint8_t major_version;
    std::uint8_t minor_version;
    std::uint64_t index_chunks_offset;
    std::uint8_t reserved[50]; // Pad to 64 bytes. Can be used in the future.
} AEON_PACK_STRUCT_POP(1);

resource_file::resource_file(const std::string &filename, io::io_filesystem_interface &filesystem_interface)
    : filename_(filename)
    , filesystem_interface_(filesystem_interface)
{
    if (filesystem_interface.exists(filename))
        __open_existing_file();
    else
        __open_new_file();
}

void resource_file::__open_existing_file()
{
    file_interface_ = filesystem_interface_.open_file(filename_, io::file_open_mode::read | io::file_open_mode::binary);
}

void resource_file::__open_new_file()
{
    file_interface_ =
        filesystem_interface_.open_file(filename_, io::file_open_mode::write | io::file_open_mode::binary);

    __write_file_header();
}

void resource_file::__write_file_header()
{
    resource_file_header header;
    memset(&header, 0, sizeof(resource_file_header));
    header.magic = 'AEON';
    header.major_version = RESOURCE_FILE_MAJOR_VERSION;
    header.minor_version = RESOURCE_FILE_MINOR_VERSION;
    header.index_chunks_offset = 0;
}

} // namespace storage
} // namespace aeon
