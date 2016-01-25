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

#include <resources/exceptions.h>
#include <resources/resource_encoding.h>
#include <memory>

namespace aeon
{
namespace resources
{

class codec
{
public:
    codec()
    {
    }
    virtual ~codec() = default;

    virtual resource_encoding get_codec_type() const = 0;
};

using codec_ptr = std::shared_ptr<codec>;

} // namespace resources
} // namespace aeon
