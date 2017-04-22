/*
 * Copyright (c) 2012-2017 Robin Degen
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include <aeon/resources/exceptions.h>
#include <aeon/resources/resource_encoding.h>
#include <aeon/resources/resource_type.h>
#include <aeon/resources/codecs/codec.h>
#include <aeon/resources/codecs/image_codec.h>
#include <aeon/resources/codecs/material_codec.h>
#include <aeon/resources/codecs/shader_codec.h>
#include <aeon/resources/codecs/atlas_codec.h>
#include <aeon/resources/codecs/mesh_codec.h>
#include <aeon/resources/codecs/scene_codec.h>
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
    auto get_scene_codec() const -> scene_codec &;

    auto get_resource_type_by_encoding(const resource_encoding encoding) const -> resource_type;

private:
    void __register_codecs();

    logger::logger logger_;
    codec_map codecs_;
};

} // namespace resources
} // namespace aeon
