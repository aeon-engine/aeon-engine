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

#include <aeon/storage/resource_file_chunk.h>

namespace aeon
{
namespace storage
{

resource_file_chunk::resource_file_chunk()
    : name_()
    , type_id_(0)
    , flags_(0)
    , offset_(0)
    , reserved_size_(0)
    , compressed_size_(0)
    , actual_size_(0)
{
}

resource_file_chunk::~resource_file_chunk() = default;

} // namespace storage
} // namespace aeon
