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

    auto get_codec_type() const -> resource_encoding override;

    auto decode(resource_manager &parent, const std::shared_ptr<shader_resource_wrapper> &wrapper) const
        -> std::shared_ptr<shader>;

private:
    enum class shader_decode_state
    {
        initial,
        parsing_vertex,
        parsing_fragment
    };

    logger::logger logger_;
};

} // namespace resources
} // namespace aeon
