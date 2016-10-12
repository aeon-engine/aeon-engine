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

#include <aeon/common/object_cache.h>
#include <aeon/gfx/gfx_buffer.h>

namespace aeon
{
namespace gfx
{

class buffer_manager
{
public:
    buffer_manager() = default;
    virtual ~buffer_manager() = default;

    buffer_ptr create_buffer(buffer_type type);

private:
    virtual buffer_ptr __create_buffer(buffer_type type) = 0;
};

} // namespace gfx
} // namespace aeon
