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

#include <data/shader.h>

namespace aeon
{
namespace data
{

shader::shader(const std::string &vertex_source, const std::string &fragment_source)
    : vertex_source_(vertex_source)
    , fragment_source_(fragment_source)
{
}

const std::string &shader::get_vertex_source() const
{
    return vertex_source_;
}

const std::string &shader::get_fragment_source() const
{
    return fragment_source_;
}

} // namespace data
} // namespace aeon
