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

#include <aeon/resources/exceptions.h>
#include <aeon/resources/resource_encoding.h>
#include <aeon/resources/codecs/codec.h>
#include <aeon/resources/shader.h>
#include <aeon/common/logger.h>

namespace aeon
{
namespace resources
{

DEFINE_EXCEPTION_OBJECT(shader_codec_decode_exception, codec_decode_exception, "Error while decoding shader resource.");

class material_resource_wrapper;
class resource_manager;

class shader_codec : public codec
{
public:
    shader_codec();
    virtual ~shader_codec() = default;

    resource_encoding get_codec_type() const override;

    std::shared_ptr<shader> decode(resource_manager &parent, const std::shared_ptr<shader_resource_wrapper> &wrapper);

private:
    enum class shader_decode_state
    {
        initial,
        parsing_vertex,
        parsing_fragment
    };

    aeon::logger::logger logger_;
};

} // namespace resources
} // namespace aeon
