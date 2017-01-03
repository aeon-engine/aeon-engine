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

#include <gfx/gles2/gfx_gles2_buffer_manager.h>
#include <gfx/gles2/gfx_gles2_buffer.h>

namespace aeon
{
namespace gfx
{
namespace gles2
{

gfx::buffer_ptr gfx_gles2_buffer_manager::__create_buffer(buffer_type type)
{
    return std::make_shared<gles2::gfx_gles2_buffer>(type);
}

} // namespace gles2
} // namespace gfx
} // namespace aeon
