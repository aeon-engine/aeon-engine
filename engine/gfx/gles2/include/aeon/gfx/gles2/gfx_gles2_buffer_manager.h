/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2017 Robin Degen
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

#include <aeon/gfx/gfx_buffer_manager.h>

namespace aeon
{
namespace gfx
{
namespace gles2
{

class gfx_gles2_buffer_manager : public gfx::buffer_manager
{
public:
    gfx_gles2_buffer_manager() = default;
    virtual ~gfx_gles2_buffer_manager() = default;

private:
    std::shared_ptr<buffer> __create_buffer(buffer_type type) override;
};

} // namespace gles2
} // namespace gfx
} // namespace aeon
