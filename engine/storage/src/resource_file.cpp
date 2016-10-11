/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2016 Robin Degen
 * All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains the property of
 * Robin Degen and its suppliers, if any. The intellectual and technical
 * concepts contained herein are proprietary to Robin Degen and its suppliers
 * and may be covered by U.S. and Foreign Patents, patents in process, and are
 * protected by trade secret or copyright law. Dissemination of this
 * information or reproduction of this material is strictly forbidden unless
 * prior written permission is obtained from Robin Degen.
 */

#include <aeon/platform/platform_filesystem_interface.h>
#include <aeon/storage/resource_file.h>
#include <aeon/platform.h>
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

resource_file::resource_file(const std::string &filename, platform::platform_filesystem_interface &filesystem_interface)
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
    file_interface_ =
        filesystem_interface_.open_file(filename_, platform::file_open_mode::read | platform::file_open_mode::binary);
}

void resource_file::__open_new_file()
{
    file_interface_ =
        filesystem_interface_.open_file(filename_, platform::file_open_mode::write | platform::file_open_mode::binary);

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
