/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2015 Robin Degen
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

#include <common/exception.h>
#include <resources/resource_type.h>
#include <aeon/utility.h>

namespace aeon
{
namespace resources
{

DEFINE_EXCEPTION_OBJECT(codec_metadata_exception, aeon::common::exception,
    "Generic Codec Metadata exception.");

DEFINE_EXCEPTION_OBJECT(codec_metadata_unknown_key_exception, codec_metadata_exception,
    "Unknown key given in Codec Metadata get_value.");

class codec_metadata
{
friend class codec;
public:
    codec_metadata()
    {
    }

    ~codec_metadata()
    {
    }

    void set_value(const std::string &key, const utility::variant &value)
    {
        data_[key] = value;
    }

    utility::variant get_value(const std::string &key)
    {
        auto result = data_.find(key);

        if (result != data_.end())
            return result->second;

        throw codec_metadata_unknown_key_exception();
    }

private:
    utility::linear_map<std::string, utility::variant> data_;
};

} // namespace resources
} // namespace aeon
