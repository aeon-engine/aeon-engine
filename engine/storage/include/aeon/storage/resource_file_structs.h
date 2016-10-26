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

#pragma once

#include <aeon/platform.h>
#include <cstdint>

namespace aeon
{
namespace storage
{

#define AEON_RESOURCE_FILE_CHUNK_NAME_MAX_LEN 88

AEON_PACK_STRUCT_PUSH(1)
struct resource_file_index_chunk
{
    std::uint8_t name[AEON_RESOURCE_FILE_CHUNK_NAME_MAX_LEN];
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
    std::uint32_t version;
    std::uint64_t index_chunks_offset;
    std::uint64_t index_chunk_count;
    std::uint8_t reserved[40]; // Pad to 64 bytes. Can be used in the future.
} AEON_PACK_STRUCT_POP(1);

} // namespace storage
} // namespace aeon
