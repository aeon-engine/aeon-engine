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

#include <resources/shader.h>

namespace aeon
{
namespace resources
{

shader::shader(resource_wrapper_ptr wrapper, const std::string &vertex_source,
               const std::string &fragment_source)
    : resource(wrapper)
    , vertex_source_(vertex_source)
    , fragment_source_(fragment_source)
{
}

shader::~shader()
{
}

} // namespace resources
} // namespace aeon
