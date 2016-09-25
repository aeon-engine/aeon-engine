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

#include <string>

namespace aeon
{
namespace data
{

class shader
{
public:
    explicit shader(const std::string &vertex_source, const std::string &fragment_source);
    ~shader() = default;

    const std::string &get_vertex_source() const;
    const std::string &get_fragment_source() const;

private:
    std::string vertex_source_;
    std::string fragment_source_;
};

} // namespace data
} // namespace aeon
