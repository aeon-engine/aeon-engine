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

#include <aeon/resources/exceptions.h>
#include <aeon/utility.h>
#include <aeon/resources/resource_encoding.h>
#include <aeon/resources/resource_type.h>
#include <aeon/resources/codecs/codec.h>
#include <aeon/resources/codecs/image_codec.h>
#include <aeon/resources/codecs/material_codec.h>
#include <aeon/resources/codecs/shader_codec.h>
#include <aeon/resources/codecs/atlas_codec.h>
#include <aeon/resources/codecs/mesh_codec.h>
#include <aeon/resources/codecs/world_codec.h>
#include <aeon/common/logger.h>
#include <map>

namespace aeon
{
namespace resources
{

DEFINE_EXCEPTION_OBJECT(codec_manager_exception, resource_exception, "Generic Codec Manager exception.");
DEFINE_EXCEPTION_OBJECT(codec_manager_unknown_codec_exception, codec_manager_exception,
                        "Unknown or unsupported codec requested from codec manager.");
DEFINE_EXCEPTION_OBJECT(codec_manager_codec_mismatch_exception, codec_manager_exception,
                        "Resource encoding does not match expected resource type.");

class codec_manager
{
    using codec_map = std::map<resource_encoding, std::shared_ptr<codec>>;

public:
    codec_manager();
    ~codec_manager() = default;

    auto get_codec(const resource_encoding encoding) const -> codec &;
    auto get_image_codec(const resource_encoding encoding) const -> image_codec &;
    auto get_material_codec() const -> material_codec &;
    auto get_shader_codec() const -> shader_codec &;
    auto get_atlas_codec() const -> atlas_codec &;
    auto get_mesh_codec(const resource_encoding encoding) const -> mesh_codec &;
    auto get_world_codec() const -> world_codec &;

    auto get_resource_type_by_encoding(const resource_encoding encoding) const -> resource_type;

private:
    void __register_codecs();

    logger::logger logger_;
    codec_map codecs_;
};

} // namespace resources
} // namespace aeon
